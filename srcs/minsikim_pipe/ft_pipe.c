/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:17:57 by bahn              #+#    #+#             */
/*   Updated: 2022/01/19 12:18:12 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				dup2(fd[i - 1][0], STDIN_FILENO);
			}
			if (content->next_flag == 2) // argv |
			{
				dup2(fd[i][1], STDOUT_FILENO);
			}
			if (content->next_flag == 3) // argv >
			{
				fd[i][1] = open(((t_command *)(*list)->next->content)->argv[0], O_WRONLY | O_CREAT | O_TRUNC, 0644); // S_IROTH : 개인에게 읽기권한
				dup2(fd[i][1], STDOUT_FILENO);
				// close(fd[i][1]);
			}
			if (content->next_flag == 4) // argv >>
			{
				fd[i][1] = open(((t_command *)(*list)->next->content)->argv[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
				dup2(fd[i][1], STDOUT_FILENO);
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
			g_data.exit_stat = ft_itoa(WEXITSTATUS(status));
			if (WEXITSTATUS(status) == 127)
				printf("minishell: %s: command not found\n", ((t_command *)(*list)->content)->argv[0]);
		}
		if ((*list)->next)
			*list = (*list)->next;
	}
}