/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2022/01/18 10:54:00 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_pipe(t_list *list, int **fd, int i)
{
	if (((t_command *)(list)->content)->next_flag == 2) // argv(입구-출력) | (출구-입력) // 알림장: >만 나왔을때 섹폴뜸;
	{
		dup2(fd[i][1], STDOUT_FILENO);
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

	size = ft_lstsize(list);
	i = -1;
	fd = malloc((sizeof(int *) * size + 1));
	while (++i < size)
	{
		fd[i] = malloc(sizeof(int) * 2);
		pipe(fd[i]);
	}
	i = -1;
	while (++i < size && list) //&& ((t_command *)(list)->content)->next_flag) // && (*list)->content
	{
		pid = fork();
		if (pid == 0)
		{
			if (((t_command *)(list)->content)->pre_flag) // (|) argv
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
			}
			if_pipe(list, fd, i);
			// if (((t_command *)(list)->content)->next_flag == 2) // argv(입구-출력) | (출구-입력) //
			// {
			// 	dup2(fd[i][1], STDOUT_FILENO);
			// }
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
			if (((t_command *)(list)->content)->next_flag == 5) // flag <
			{
				exe = list->content;
				while (((t_command *)(list)->content)->next_flag == 5)
				{
					fd[i][0] = open(((t_command *)(list)->next->content)->argv[0], O_RDONLY, 0644);
					dup2(fd[i][0], STDIN_FILENO);
					close(fd[i][0]);
					if (((t_command *)(list)->next->content)->next_flag != 5) // aa > bb > cc
					{
						break ;
					}
					list = (list)->next;
				}
				to_execve_2(exe);
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
				{
					break ; /////////// ㅇㅕ기서 분기
					// return (list);
				}
				list = (list)->next;
			}
			while (((t_command *)(list)->content)->next_flag == 5)
			{
				if (((t_command *)(list)->next->content)->next_flag != 5) // aa > bb > cc
				{
					break ;
				}
				list = (list)->next;
			}
		}
		if ((list)->next)
		{
			list = (list)->next;
		}
		else if (((t_command *)(list)->content)->next_flag == 0)
			return (list);
	}
	return (list);
}