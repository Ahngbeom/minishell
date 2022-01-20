/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 18:50:15 by bahn              #+#    #+#             */
/*   Updated: 2022/01/20 14:22:00 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_execve(t_command *command)
{
	char	*cmd_path;
	char	**envp;
	pid_t	execve_pid;
	int		status;

	cmd_path = execfile_finder(command->argv[0]);
	envp = envp_to_arr_converter(g_data.lst_env);
	execve_pid = fork();
	if (execve_pid < 0)
		exit(EXIT_FAILURE);
	else if (execve_pid == 0)
	{
		if (cmd_path == NULL)
			exit(127);
		if (execve(cmd_path, command->argv, envp) == -1)
			exit(errno);
	}
	waitpid(execve_pid, &status, 0);
	if (WEXITSTATUS(status) == 127)
		printf("minishell: %s: command not found\n", command->argv[0]);
	free(g_data.exit_stat);
	g_data.exit_stat = ft_itoa(WEXITSTATUS(status));
	printf("status : %d\n", WEXITSTATUS(status));
	printf("exit status : %s\n", g_data.exit_stat);
	if (cmd_path != NULL)
		free(cmd_path);
	if (envp != NULL)
		split_free(envp);
	return (status);
}

int	to_execve_2(t_command *command)
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = execfile_finder(command->argv[0]);
	// printf("cmd_path:%s\n", cmd_path);
	if (cmd_path == NULL)
		exit(127);
	if (execve(cmd_path, command->argv, NULL) == -1)
		exit(errno);
	exit(EXIT_SUCCESS);
}

// int	to_execve_3(char **argv)
// {
// 	char	*cmd_path;

// 	cmd_path = NULL;
// 	cmd_path = execfile_finder(argv[0]);
// 	printf("cmd_path:%s\n", cmd_path);
// 	if (cmd_path == NULL)
// 		exit(127);
// 	if (execve(cmd_path, argv, NULL) == -1)
// 		exit(errno);
// 	exit(EXIT_SUCCESS);
// }
