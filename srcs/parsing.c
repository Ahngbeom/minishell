/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/13 14:23:17 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	command_finder(char *command)
{
	if (!ft_strncmp(command, "echo", ft_strlen("echo")))
		return (echo_option_checker());
	else if (!ft_strncmp(command, "cd", ft_strlen("cd")))
		return (change_dir());
	else if (!ft_strncmp(command, "pwd", ft_strlen("pwd")))
		return (0);
	else if (!ft_strncmp(command, "export", ft_strlen("export")))
		return (0);
	else if (!ft_strncmp(command, "unset", ft_strlen("unset")))
		return (0);
	else if (!ft_strncmp(command, "env", ft_strlen("env")))
		return (0);
	else if (!ft_strncmp(command, "exit", ft_strlen("exit")))
		return (0);
	else
		return (1);
}

int	parsing(void)
{
	pid_t	execve_pid;
	int		status;
	int		rtn;

	g_data.argv = ft_split(g_data.input, ' ');
	rtn = command_finder(g_data.argv[0]);
	if (rtn == 0)
	{
		execve_pid = fork();
		if (execve_pid < 0)
			exit(EXIT_FAILURE);
		else if (execve_pid == 0)
		{
			g_data.cmd_path = ft_strjoin(g_data.bin_path, g_data.argv[0]);
			if (execve(g_data.cmd_path, g_data.argv, g_data.env) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{	
			waitpid(execve_pid, &status, 0);
			add_history(g_data.input);
		}
		return (rtn);
	}
	else if (rtn < 0)
		return (rtn);
	else
		return (rtn);
}
