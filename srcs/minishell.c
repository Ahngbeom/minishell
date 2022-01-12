/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2022/01/12 13:09:42 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_flag(t_list *i_list)
{
	t_list	*list;
	t_command	*content;
	t_command	*next_con;

	list = i_list;
	while (list->next)
	{
		content = (t_command *)list->content;
		next_con = (t_command *)list->next->content;
		if (ft_strncmp(content->redirect, ";", 2) == 0)
		{
			content->next_flag = 1;
			next_con->pre_flag = 1;
		}
		if (ft_strncmp(content->redirect, "|", 2) == 0)
		{
			content->next_flag = 2;
			next_con->pre_flag = 2;
		}
		if (ft_strncmp(content->redirect, ">", 2) == 0)
		{
			content->next_flag = 3;
			next_con->pre_flag = 3;
		}
		if (ft_strncmp(content->redirect, ">>", 3) == 0)
		{
			content->next_flag = 4;
			next_con->pre_flag = 4;
		}
		if (ft_strncmp(content->redirect, "<", 2) == 0)
		{
			content->next_flag = 5;
			next_con->pre_flag = 5;
		}
		if (ft_strncmp(content->redirect, "<<", 2) == 0)
		{
			content->next_flag = 6;
			next_con->pre_flag = 6;
		}
		list = list->next;
	}
}

t_list	**dup2_fd(t_list **list, int **fd, int i) // if > > > > ...
{
	// t_list		*ptr;
	t_command	*cont;

	// ptr = *list;
	while (1)
	{
		cont = (*list)->content;
		if (cont->next_flag == 3) // >
		{
			fd[i][1] = open(((t_command *)(*list)->next->content)->argv[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(fd[i][1], STDOUT_FILENO);
			close(fd[i][1]);
		}
		else
			break ;
		*list = (*list)->next;
	}
	return (list);
}

void	ft_pipe(t_list	**list)
{
	int		**fd;
	int		i;
	int		size;
	t_command	*content;
	t_command	*exe;
	t_list		*ptr;
	pid_t		pid;
	int			status;

	size = ft_lstsize(g_data.commands);
	fd = malloc(sizeof(int *) * size);
	ptr = *list;
	exe = (*list)->content;
	i = -1;
	while (++i < size)
	{
		fd[i] = malloc(sizeof(int) * 2);
		pipe(fd[i]);
	}
	exe = (t_command *)(*list)->content;
	i = -1;
	while (++i < size && (*list)->content != NULL)
	{
		content = (*list)->content;
		pid = fork();
		if (pid == 0) // son
		{
			if (content->pre_flag == 2) // | argv
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
			}
			if (content->next_flag == 2) // argv |
			{
				dup2(fd[i][1], STDOUT_FILENO);
			}
			
			////////////////////////////////////////////////////////////
			
			if (content->pre_flag == 3 || content->pre_flag == 4) // (IN) > argv(OUT)
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
			}
			if (content->next_flag == 3) // argv >
			{
				list = dup2_fd(list, fd, i);
				// fd[i][1] = open(((t_command *)(*list)->next->content)->argv[0], O_RDWR | O_CREAT | O_TRUNC, 0644); // S_IROTH : 개인에게 읽기권한 , 0644: 소유자-WR,RD 그룹,개인-RD
				// dup2(fd[i][1], STDOUT_FILENO);
			}
			if (content->next_flag == 4) // argv >>
			{
				fd[i][1] = open(((t_command *)(*list)->next->content)->argv[0], O_RDWR | O_CREAT | O_APPEND, 0644);
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][1]);
			}
			if (content->pre_flag == 5) // < argv
			{
				dup2(fd[i - 1][1], STDOUT_FILENO);
			}
			if (content->next_flag == 5) // argv <
			{
				fd[i][0] = open(((t_command *)(*list)->next->content)->argv[0], O_RDONLY, 0644);
				dup2(fd[i][0], STDIN_FILENO);
				close(fd[i][0]);
				if (((t_command *)(*list)->next->content)->next_flag == 3)
				{
					printf("why..\n");
					dup2(fd[i + 1][1], STDIN_FILENO);
					close(fd[i + 1][1]);
				}
			}
			if (content->next_flag == 6) //argv <<
			{
				fd[i][1] = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
				dup2(fd[i][1], STDOUT_FILENO);
			}
			if (content->pre_flag == 6) // << argv
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
				// to_execve_2((*list - sizeof(*list))->content);
			}
			to_execve_2(exe); ///
		}
		else // parent
		{
			wait(&status);
			
			if (content->pre_flag)
				close(fd[i - 1][0]);
			if (content->next_flag)
				close(fd[i][1]);
			if (content->next_flag == 6) // rm temp
				unlink("temp");
			g_data.status = WEXITSTATUS(g_data.status);
			if (g_data.status == 127)
				printf("minishell: %s: command not found\n", ((t_command *)(*list)->content)->argv[0]);
		}
		if ((*list)->next)
			*list = (*list)->next;
		i++;
	}
}

int	minishell(char *input)
{
	t_list		*list;
	t_command	*cmd;

	input = escape_sequence(input);
	add_history(input);
	input = remove_enclosed_quotes(input);
	input_split(&g_data.commands, ft_strtrim(input, " "));
	free(input);
	set_flag(g_data.commands);
	list = g_data.commands;
	while (list != NULL)
	{
		cmd = list->content;
		if (cmd->redirect != NULL) // not NULL, not ;
		{
			ft_pipe(&(list));
		}
		else
		{
			parsing(cmd);
			if (!cmd->bulit_in_flag)
				to_execve(cmd);
		}
		list = list->next;
	}
	ft_lstclear(&g_data.commands, command_free);
	return (0);
}
