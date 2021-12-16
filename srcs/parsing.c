/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/16 16:16:10 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	command_finder(char *command)
{
	if (!ft_strncmp(command, "echo", ft_strlen(command)))
		return (minishell_echo());
	else if (!ft_strncmp(command, "cd", ft_strlen(command)))
		return (minishell_cd());
	else if (!ft_strncmp(command, "pwd", ft_strlen(command)))
		return (minishell_pwd());
	else if (!ft_strncmp(command, "export", ft_strlen(command)))
		return (minishell_export());
	else if (!ft_strncmp(command, "unset", ft_strlen(command)))
		return (0);
	else if (!ft_strncmp(command, "env", ft_strlen(command)))
		return (minishell_env());
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
			if (execve(g_data.current_path, g_data.argv, g_data.env) == -1)
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
