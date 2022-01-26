/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 20:26:15 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_pipe(t_list *list, int **fd, int i)
{
	if (((t_command *)(list)->content)->next_flag == 2)
	{
		close(fd[i][0]);
		dup2(fd[i][1], STDOUT_FILENO);
	}
}

void	if_flag_right(t_list *list, t_command *exe, int **fd, int i)
{
	if (((t_command *)(list)->content)->next_flag == 3 || \
		((t_command *)(list)->content)->next_flag == 4)
	{
		exe = list->content;
		while (((t_command *)(list)->content)->next_flag == 3 || \
			((t_command *)(list)->content)->next_flag == 4)
		{
			if (((t_command *)(list)->content)->next_flag == 3)
				fd[i][1] = open(((t_command *)(list)->next->content)->argv[0], \
				O_RDWR | O_CREAT | O_TRUNC, 0644);
			else
				fd[i][1] = open(((t_command *)(list)->next->content)->argv[0], \
				O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(fd[i][1], STDOUT_FILENO);
			close(fd[i][0]);
			if (((t_command *)(list)->next->content)->next_flag != 3 && \
				((t_command *)(list)->next->content)->next_flag != 4)
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
	if (((t_command *)(list)->content)->next_flag == 3 || \
		((t_command *)(list)->content)->next_flag == 4)
	{
		while (((t_command *)(list)->content)->next_flag == 3 || \
			((t_command *)(list)->content)->next_flag == 4)
		{
			if (((t_command *)(list)->content)->next_flag == 3)
				fd[i][1] = open(((t_command *)(list)->next->content)->argv[0], \
					O_RDWR | O_CREAT | O_TRUNC, 0644);
			else
				fd[i][1] = open(((t_command *)(list)->next->content)->argv[0], \
					O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(fd[i][1], STDOUT_FILENO);
			close(fd[i][0]);
			if (((t_command *)(list)->next->content)->next_flag != 3 && \
				((t_command *)(list)->next->content)->next_flag != 4)
			{
				break ;
			}
			list = (list)->next;
		}
	}
}

void	if_flag_left(t_list *list, t_command *exe, int **fd, int *i)
{
	if (((t_command *)(list)->content)->next_flag == 5)
	{
		exe = list->content;
		while (((t_command *)(list)->content)->next_flag == 5)
		{
			fd[*i][1] = open(\
				((t_command *)(list)->next->content)->argv[0], O_RDONLY, 0644);
			dup2(fd[*i][1], STDIN_FILENO);
			close(fd[*i][0]);
			if (((t_command *)(list)->next->content)->next_flag == 3 || \
				((t_command *)(list)->next->content)->next_flag == 4)
			{
				list = (list)->next;
				(*i)++;
				if_flag_right_no_exe(list, fd, *i);
				to_execve_2(exe);
			}
			if (((t_command *)(list)->next->content)->next_flag != 5)
			{
				break ;
			}
			list = (list)->next;
		}
		to_execve_2(exe);
	}
}
