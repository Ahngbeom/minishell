/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 18:50:15 by bahn              #+#    #+#             */
/*   Updated: 2021/12/29 20:11:22 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_execve(t_command *command)
{
	char	*cmd_path;
	pid_t	execve_pid;

	cmd_path = NULL;
	execve_pid = fork();
	if (execve_pid < 0)
		exit(EXIT_FAILURE);
	else if (execve_pid == 0)
	{
		cmd_path = execfile_finder(command->argv[0]);
		if (cmd_path == NULL)
			exit(127);
		if (execve(cmd_path, command->argv, NULL) == -1)
			exit(errno);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(execve_pid, &g_data.status, 0);
		g_data.status = WEXITSTATUS(g_data.status);
		if (g_data.status == 127)
			printf("minishell: %s: command not found\n", command->argv[0]);
		if (cmd_path != NULL)
			free(cmd_path);
	}
	return (0);
}
