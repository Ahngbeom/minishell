/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 18:50:15 by bahn              #+#    #+#             */
/*   Updated: 2021/12/29 12:31:16 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_execve(t_command *command)
{
	char	*cmd_path;
	pid_t	execve_pid;
	int		status;

	cmd_path = NULL;
	execve_pid = fork();
	if (execve_pid < 0)
		exit(EXIT_FAILURE);
	else if (execve_pid == 0)
	{
		// cmd_path = ft_strjoin(BIN_PATH, command->argv[0]);
		cmd_path = execfile_finder(command->argv[0]);
		if (execve(cmd_path, command->argv, NULL) == -1) // execve 에서 envp는 NULL?
		{
			printf("minishell: %s: command not found\n", command->argv[0]);
			// g_data.status = errno;
			printf("errno : %d\n", errno);
			exit(errno);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(execve_pid, &status, 0);
		printf("EXIT STATUS : %d\n", status);
		if (cmd_path != NULL)
			free(cmd_path);
	}
	return (0);
}
