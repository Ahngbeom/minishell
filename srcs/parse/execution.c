/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2022/01/18 21:52:29 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution(t_command *command, int input_fd)
{
	t_pipe	pipe_data;
	pid_t	pid;
	int		stat_loc;

	set_pipe(&pipe_data);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		close(pipe_data.fd[READ]);
		close(pipe_data.fd[WRITE]);
		if (input_fd != -1)
			dup2(input_fd, STDIN_FILENO);
		exit(to_execve(command));
	}
	waitpid(pid, &stat_loc, 0);
	printf("execution exit status : %s\n", g_data.exit_stat);
	if (input_fd != -1)
		close(input_fd);
	return (release_pipe(&pipe_data));
}
