/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/21 14:44:33 by bahn             ###   ########.fr       */
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

int	parsing(int	i)
{
	pid_t	execve_pid;//
	int		status;//
	int		rtn;//

	g_data.argv = ft_split(g_data.split_input[i], ' ');
	rtn = command_finder(g_data.argv[0]);
	if (rtn == EXEC_PROC)
	{
		execve_pid = fork();
		if (execve_pid < 0)
			exit(EXIT_FAILURE);
		else if (execve_pid == 0)
		{
			// free(g_data.argv);
			g_data.cmd_path = ft_strjoin(BIN_PATH, g_data.argv[0]);
			// execve 에서 envp는 NULL?
			if (execve(g_data.cmd_path, g_data.argv, NULL) == -1)
			{
				// printf("execve Error: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
		else
		{	
			waitpid(execve_pid, &status, 0);
			add_history(g_data.input);
			// free(g_data.input);
		}
		return (0);
	}
	else
		return (rtn);
}
