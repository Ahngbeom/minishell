/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2022/01/17 19:30:06 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution(t_command *command, int input_fd)
{
	pid_t	pid;
	int		fd[2];
	int		stat_loc;
	int		org_stdin;
	int		org_stdout;

	org_stdin = dup(STDIN_FILENO);
	org_stdout = dup(STDOUT_FILENO);
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		if (input_fd != -1)
			dup2(input_fd, STDIN_FILENO);
		else
			exit(to_execve(command));
	}
	close(fd[WRITE]);
	waitpid(pid, &stat_loc, 0);
	if (input_fd != -1)
		close(input_fd);
	dup2(org_stdin, STDIN_FILENO);
	dup2(org_stdout, STDOUT_FILENO);
	return (fd[READ]);
}
