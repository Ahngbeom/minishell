/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/21 17:07:40 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	command_finder(char *command)
{
	if (!ft_strncmp(command, "echo", ft_strlen("echo") + 1))
		return (minishell_echo());
	else if (!ft_strncmp(command, "cd", ft_strlen("cd") + 1))
		return (minishell_cd());
	else if (!ft_strncmp(command, "pwd", ft_strlen("pwd") + 1))
		return (minishell_pwd());
	else if (!ft_strncmp(command, "export", ft_strlen("export") + 1))
		return (minishell_export());
	else if (!ft_strncmp(command, "unset", ft_strlen("unset") + 1))
		return (minishell_unset());
	else if (!ft_strncmp(command, "env", ft_strlen("env") + 1))
		return (minishell_env());
		// return (EXEC_PROC);
	else
		return (EXEC_PROC);
}

// static	void	command_finder2(char *command)
// {
// 	if (!ft_strncmp(command, "echo", ft_strlen("echo") + 1))
// 		g_data.command_fp = minishell_echo;
// 	else if (!ft_strncmp(command, "cd", ft_strlen("cd") + 1))
// 		g_data.command_fp = minishell_cd;
// 	else if (!ft_strncmp(command, "pwd", ft_strlen("pwd") + 1))
// 		g_data.command_fp = minishell_pwd;
// 	else if (!ft_strncmp(command, "export", ft_strlen("export") + 1))
// 		g_data.command_fp = minishell_export;
// 	else if (!ft_strncmp(command, "unset", ft_strlen("unset") + 1))
// 		g_data.command_fp = minishell_unset;
// 	else if (!ft_strncmp(command, "env", ft_strlen("env") + 1))
// 		g_data.command_fp = minishell_env;
// }

void	parsing(char *str)
{
	char	*cmd_path;
	pid_t	execve_pid;
	int		status;

	cmd_path = NULL;
	g_data.argv = ft_split(str, ' ');

	// execve_pid = fork();
	// if (execve_pid < 0)
	// 	exit(EXIT_FAILURE);
	// else if (execve_pid == 0)
	// {
	// 	command_finder2(g_data.argv[0]);
	// 	if (g_data.command_fp != NULL)
	// 	{
	// 		g_data.command_fp();
	// 		g_data.command_fp = NULL;
	// 		exit(EXIT_SUCCESS);
	// 	}
	// 	else
	// 	{
	// 		cmd_path = ft_strjoin(BIN_PATH, g_data.argv[0]);
	// 		if (execve(cmd_path, g_data.argv, NULL) == -1) // execve 에서 envp는 NULL?
	// 		{
	// 			printf("bash: %s: command not found\n", g_data.argv[0]);
	// 			exit(EXIT_FAILURE);
	// 		}
	// 	}
	// }
	// else
	// {
	// 	waitpid(execve_pid, &status, 0);
	// 	if (cmd_path != NULL)
	// 		free(cmd_path);
	// }

	if (command_finder(g_data.argv[0]) == EXEC_PROC)
	{
		execve_pid = fork();
		if (execve_pid < 0)
			exit(EXIT_FAILURE);
		else if (execve_pid == 0)
		{
			cmd_path = ft_strjoin(BIN_PATH, g_data.argv[0]);
			if (execve(cmd_path, g_data.argv, NULL) == -1) // execve 에서 envp는 NULL?
			{
				printf("bash: %s: command not found\n", g_data.argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(execve_pid, &status, 0);
			if (cmd_path != NULL)
				free(cmd_path);
		}
	}
}
