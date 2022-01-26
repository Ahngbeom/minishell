/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_flag_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 16:06:09 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_son_2(t_list *list, t_pip pip, int *i, int out_fd)
{
	char	*temp;

	pip.fd[*i][1] = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
	while (1)
	{
		temp = readline("> ");
		if (ft_strncmp(temp, ((t_command *)(list)->next->content)-> \
			argv[0], ft_strlen(((t_command *)(list)->next->content)-> \
				argv[0]) + 1) == 0)
			exit(0);
		dup2(pip.fd[*i][1], STDOUT_FILENO);
		printf("%s\n", temp);
		free(temp);
		dup2(out_fd, STDOUT_FILENO);
	}
}

void	do_son(t_list *list, t_pip pip)
{
	pip.exe = list->content;
	if (((t_command *)(list)->content)->pre_flag)
	{
		dup2(pip.fd[pip.i - 1][0], STDIN_FILENO);
		close(pip.fd[pip.i - 1][1]);
		close(pip.fd[pip.i - 1][0]);
	}
	if_pipe(list, pip.fd, pip.i);
	if_flag_right(list, pip.exe, pip.fd, pip.i);
	if_flag_left(list, pip.exe, pip.fd, &(pip.i));
	if_flag_d_left(list, pip.exe, pip, &(pip.i));
	to_execve_2(list->content);
}

void	if_flag_d_left(t_list *list, t_command *exe, t_pip pip, int *i)
{
	int		out_fd;

	if (((t_command *)(list)->content)->next_flag == 6)
	{
		out_fd = dup(STDOUT_FILENO);
		pip.pid = fork();
		if (pip.pid == 0)
			do_son_2(list, pip, i, out_fd);
		wait(&pip.status);
		pip.fd[*i][1] = open("temp", O_RDONLY, 0644);
		dup2(pip.fd[*i][1], STDIN_FILENO);
		close(pip.fd[*i][1]);
		if (((t_command *)(list)->next->content)->next_flag == 3 || \
			((t_command *)(list)->next->content)->next_flag == 4)
		{
			exe = list->content;
			list = (list)->next;
			(*i)++;
			if_flag_right_no_exe(list, pip.fd, *i);
			to_execve_2(exe);
		}
		to_execve_2(list->content);
	}
}

void	while_3456(t_list **list, int *i)
{
	while_34(list);
	while (((t_command *)(*list)->content)->next_flag == 5 || \
		((t_command *)(*list)->content)->next_flag == 6)
	{
		if (((t_command *)(*list)->next->content)->next_flag == 3 || \
			((t_command *)(*list)->next->content)->next_flag == 4)
		{
			*list = (*list)->next;
			(*i)++;
			while (((t_command *)(*list)->content)->next_flag == 3 || \
				((t_command *)(*list)->content)->next_flag == 4)
			{
				if (((t_command *)(*list)->next->content)->next_flag != 3 && \
					((t_command *)(*list)->next->content)->next_flag != 4)
					break ;
				*list = (*list)->next;
			}
		}
		if (((t_command *)(*list)->next->content)->next_flag != 5)
			break ;
		*list = (*list)->next;
	}
}

void	while_34(t_list **list)
{
	if (((t_command *)(*list)->content)->next_flag == 6)
		unlink("temp");
	while (((t_command *)(*list)->content)->next_flag == 3 || \
		((t_command *)(*list)->content)->next_flag == 4)
	{
		if (((t_command *)(*list)->next->content)->next_flag != 3 && \
			((t_command *)(*list)->next->content)->next_flag != 4)
			break ;
		*list = (*list)->next;
	}
}
