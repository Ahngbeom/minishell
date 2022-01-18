/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2022/01/18 14:29:47 by minsikim         ###   ########.fr       */
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

void	if_pipe(t_list *list, int **fd, int i)
{
	if (((t_command *)(list)->content)->next_flag == 2) // argv(입구-출력) | (출구-입력) // 알림장: >만 나왔을때 섹폴뜸; -> ok
	{
		dup2(fd[i][1], STDOUT_FILENO);
	}
}

void	if_flag_right(t_list *list, t_command *exe, int **fd, int i)
{
	if (((t_command *)(list)->content)->next_flag == 3 || ((t_command *)(list)->content)->next_flag == 4) // > or >>
	{
		exe = list->content;
		while (((t_command *)(list)->content)->next_flag == 3 || ((t_command *)(list)->content)->next_flag == 4) // > 또는 >>
		{
			if (((t_command *)(list)->content)->next_flag == 3)
				fd[i][1] = open(((t_command *)(list)->next->content)->argv[0], O_RDWR | O_CREAT | O_TRUNC, 0644); // S_IROTH : 개인에게 읽기권한 , 0644: 소유자-WR,RD 그룹,개인-RD
			else
				fd[i][1] = open(((t_command *)(list)->next->content)->argv[0], O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(fd[i][1], STDOUT_FILENO);
			close(fd[i][1]);
			if (((t_command *)(list)->next->content)->next_flag != 3  && ((t_command *)(list)->next->content)->next_flag != 4) // aa > bb > cc
			{
				break ;
			}
			list = (list)->next;
		}
		to_execve_2(exe);
	}
}

void	if_flag_right_no_exe(t_list *list, int **fd, int i)
{
	if (((t_command *)(list)->content)->next_flag == 3 || ((t_command *)(list)->content)->next_flag == 4) // > or >>
	{
		while (((t_command *)(list)->content)->next_flag == 3 || ((t_command *)(list)->content)->next_flag == 4) // > 또는 >>
		{
			if (((t_command *)(list)->content)->next_flag == 3)
				fd[i][1] = open(((t_command *)(list)->next->content)->argv[0], O_RDWR | O_CREAT | O_TRUNC, 0644); // S_IROTH : 개인에게 읽기권한 , 0644: 소유자-WR,RD 그룹,개인-RD
			else
				fd[i][1] = open(((t_command *)(list)->next->content)->argv[0], O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(fd[i][1], STDOUT_FILENO);
			close(fd[i][1]);
			if (((t_command *)(list)->next->content)->next_flag != 3  && ((t_command *)(list)->next->content)->next_flag != 4) // aa > bb > cc
			{
				break ;
			}
			list = (list)->next;
		}
	}
}

void	if_flag_left(t_list *list, t_command *exe, int **fd, int i)
{
	if (((t_command *)(list)->content)->next_flag == 5) // flag <
	{
		exe = list->content;
		// printf("test_argv:%s\n", exe->argv[0]);
		while (((t_command *)(list)->content)->next_flag == 5)
		{
			fd[i][1] = open(((t_command *)(list)->next->content)->argv[0], O_RDONLY, 0644);
			dup2(fd[i][1], STDIN_FILENO);
			close(fd[i][1]);
			if (((t_command *)(list)->next->content)->next_flag == 3) // ~ < ~ >
			{
				// printf("hi >!!\n");
				list = (list)->next;
				i++;
				if_flag_right_no_exe(list, fd, i);
				// printf("test_argv:%s\n", exe->argv[0]); // ???
				to_execve_2(exe);
			}
			if (((t_command *)(list)->next->content)->next_flag != 5) // aa > bb > cc
			{
				// printf("hi(b)\n");
				break ;
			}
			// printf("hi(2)\n");
			list = (list)->next;
		}
		// printf("test_argv:%s\n", exe->argv[0]);
		to_execve_2(exe);
	}
}

t_list	*ft_pipe(t_list *list)
{
	int		size;
	int		i;
	int		**fd;
	pid_t	pid;
	int		status;
	t_command	*exe;

	exe = NULL; //
	size = ft_lstsize(list);
	i = -1;
	fd = malloc((sizeof(int *) * size + 1));
	while (++i < size)
	{
		fd[i] = malloc(sizeof(int) * 2);
		pipe(fd[i]);
	}
	i = -1;
	while (++i < size && ((t_command *)(list)->content)->next_flag) //&& ((t_command *)(list)->content)->next_flag) // && (*list)->content
	{
		pid = fork();
		if (pid == 0)
		{
			if (((t_command *)(list)->content)->pre_flag) // (|) argv
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
			}
			if_pipe(list, fd, i);
			if_flag_right(list, exe, fd, i); // flag 3: >, 4: >>
			if_flag_left(list, exe, fd, i); // flag 5: <
			if (((t_command *)(list)->content)->next_flag == 6) // <<
			{
				fd[i][1] = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][1]);
			}
			if (((t_command *)(list)->content)->next_flag == 3 || ((t_command *)(list)->content)->next_flag == 4)
				exit(0);
			to_execve_2(list->content); // 만약 다음 플레그가 > 라면 그냥 나가야함
		}
		else // pid == 1
		{
			wait(&status);
			g_data.status = WEXITSTATUS(g_data.status);
			if (((t_command *)(list)->content)->pre_flag)
				close(fd[i - 1][0]); // for pipe
			if (((t_command *)(list)->content)->next_flag) ////////// close
				close(fd[i][1]);
			while (((t_command *)(list)->content)->next_flag == 3 || ((t_command *)(list)->content)->next_flag == 4) // >
			{
				if (((t_command *)(list)->next->content)->next_flag != 3 && ((t_command *)(list)->next->content)->next_flag != 4) // aa > bb > cc
					break ;
				list = (list)->next;
			}
			while (((t_command *)(list)->content)->next_flag == 5)
			{
				if (((t_command *)(list)->next->content)->next_flag == 3) // ~ < ~ >
				{
					list = (list)->next;
					i++;
					while (((t_command *)(list)->content)->next_flag == 3 || ((t_command *)(list)->content)->next_flag == 4) // >
					{
						if (((t_command *)(list)->next->content)->next_flag != 3 && ((t_command *)(list)->next->content)->next_flag != 4) // aa > bb > cc
							break ;
						list = (list)->next;
					}
				}
				if (((t_command *)(list)->next->content)->next_flag != 5) // aa > bb > cc
					break ;
				list = (list)->next;
			}
		}
		if (((t_command *)(list)->content)->next_flag == 6) // <<
		{
			pid = fork();
			if (pid == 0)
			{
				fd[i][1] = open("temp", O_RDONLY, 0644);
				dup2(fd[i][1], STDIN_FILENO);
				close(fd[i][1]);
				// printf("argv:%s\n", ((t_command *)(list)->next->content)->argv[0]);
				to_execve_2(list->content);
			}
			wait(&status);
			g_data.status = WEXITSTATUS(g_data.status);
			close(fd[i][1]);
			unlink("temp");
		}
		if ((list)->next)
			list = (list)->next;
		else if (((t_command *)(list)->content)->next_flag == 0)
			return (list);
	}
	return (list);
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
		if (cmd->next_flag) // |
		{
			printf("(1)\n");
			// ft_pipe(list);
			list = ft_pipe(list);
			break ;
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
