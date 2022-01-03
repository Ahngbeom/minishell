/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2022/01/04 08:35:32 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	specific_processing(char *input)
{
	char	*trim;

	trim = ft_strtrim(input, " ");
	if (trim == NULL || !ft_strncmp(trim, "exit", ft_strlen("exit") + 1))
	{
		ft_putendl_fd("exit", 1);
		if (input != NULL)
			free(input);
		if (trim != NULL)
			free(trim);
		return (-1);
	}
	else if (ft_strlen(trim) == 0)
	{
		if (input != NULL)
			free(input);
		if (ft_strlen(trim) > 0)
			free(trim);
		return (1);
	}
	else
		return (0);
}

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
		list = list->next;
	}
}

void	ft_pipe(t_list	**list)
{
	int		**fd;
	int		i;
	int		size;
	t_command	*content;
	pid_t		pid;
	int			status;

	size = ft_lstsize(g_data.commands);
	fd = malloc(sizeof(int *) * size);
	i = -1;
	while (++i < size)
	{
		fd[i] = malloc(sizeof(int) * 2);
	}
	i = -1;
	while (++i < size && (*list)->content != NULL)
	{
		content = (*list)->content;
		pipe(fd[i]);
		pid = fork();
		if (pid == 0) // son
		{
			if (content->pre_flag == 2) // | argv
			{
				dup2(fd[i - 1][0], 0);
			}
			if (content->next_flag == 2) // argv |
			{
				dup2(fd[i][1], 1);
			}
			to_execve_2((*list)->content);
		}
		else // parent
		{
			wait(&status);
			if (content->pre_flag == 2)
				close(fd[i - 1][0]);
			if (content->next_flag == 2)
			close(fd[i][1]);
			g_data.status = WEXITSTATUS(g_data.status);
			if (g_data.status == 127)
				printf("minishell: %s: command not found\n", ((t_command *)(*list)->content)->argv[0]);
		}
		if ((*list)->next)
			*list = (*list)->next;
	}
}

int	minishell(char *input)
{
	int			status;
	t_list		*ptr;

	status = specific_processing(input);
	if (status)
		return (status);
	input = escape_sequence(input);
	add_history(input);
	input = remove_enclosed_quotes(input);
	input_split(&g_data.commands, ft_strtrim(input, " "));
	free(input);
	set_flag(g_data.commands); //
	ptr = g_data.commands;
	while (ptr != NULL)
	{
		if (((t_command *)ptr->content)->redirect != NULL) // redirect가 있다면
		{
			ft_pipe(&(ptr));
		}
		else
		{
			parsing(((t_command *)ptr->content));
			if (!((t_command *)ptr->content)->bulit_in_flag)
				to_execve(((t_command *)ptr->content));
		}
		ptr = ptr->next;
	}
	ft_lstclear(&g_data.commands, command_free);
	return (0);
}
