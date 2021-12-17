/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/17 16:36:51 by bahn             ###   ########.fr       */
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
		// return (minishell_export());
		return (minishell_export2());
	else if (!ft_strncmp(command, "unset", ft_strlen("unset") + 1))
		return (minishell_unset());
	else if (!ft_strncmp(command, "env", ft_strlen("env") + 1))
		// return (minishell_env());
		return (minishell_env2());
	else
		return (-1);
}

int	parsing(void)
{
	pid_t	execve_pid;
	int		status;
	int		rtn;

	g_data.argv = ft_split(g_data.input, ' ');
	rtn = command_finder(g_data.argv[0]);
	if (rtn == EXEC_PROC)
	{
		execve_pid = fork();
		if (execve_pid < 0)
			exit(EXIT_FAILURE);
		else if (execve_pid == 0)
		{
			free(g_data.argv);
			if (execve(g_data.current_path, g_data.argv, NULL) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{	
			waitpid(execve_pid, &status, 0);
			add_history(g_data.input);
		}
		return (rtn);
	}
	else
		return (rtn);
}
