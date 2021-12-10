/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/11 00:48:37 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_finder(char *command)
{
	if (!ft_strncmp(command, "echo", ft_strlen(g_data.input)))
		return (0);
	else if (!ft_strncmp(command, "cd", ft_strlen(g_data.input)))
		return (change_dir());
	else if (!ft_strncmp(command, "pwd", ft_strlen(g_data.input)))
		return (0);
	else if (!ft_strncmp(command, "export", ft_strlen(g_data.input)))
		return (0);
	else if (!ft_strncmp(command, "unset", ft_strlen(g_data.input)))
		return (0);
	else if (!ft_strncmp(command, "env", ft_strlen(g_data.input)))
		return (0);
	else if (!ft_strncmp(command, "exit", ft_strlen(g_data.input)))
		return (0);
	else
		return (1);
}

int	parsing(void)
{
	pid_t	execve_pid;
	int		status;
	char	*cmd_path;

	g_data.argv = ft_split(g_data.input, ' ');
	if (!command_finder(g_data.argv[0]))
	{
		execve_pid = fork();
		if (execve_pid < 0)
			exit(EXIT_FAILURE);
		else if (execve_pid == 0)
		{
			cmd_path = ft_strjoin("/bin/", g_data.argv[0]);
			if (execve(cmd_path, g_data.argv, g_data.env) == -1)
				exit(EXIT_FAILURE);
		}
		else
			wait(&status);
		free(cmd_path);
		return (0);
	}
	else
		return (1);
}
