/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 18:50:15 by bahn              #+#    #+#             */
/*   Updated: 2022/01/16 20:36:51 by minsikim         ###   ########.fr       */
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

int	to_execve_2(t_command *command)
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = execfile_finder(command->argv[0]);
	printf("cmd_path:%s\n", cmd_path);
	if (cmd_path == NULL)
		exit(127);
	if (execve(cmd_path, command->argv, NULL) == -1)
		exit(errno);
	exit(EXIT_SUCCESS);
}

int	to_execve_3(char **argv)
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = execfile_finder(argv[0]);
	printf("cmd_path:%s\n", cmd_path);
	if (cmd_path == NULL)
		exit(127);
	if (execve(cmd_path, argv, NULL) == -1)
		exit(errno);
	exit(EXIT_SUCCESS);
}
