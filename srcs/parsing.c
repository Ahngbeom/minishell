/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/21 13:33:28 by minsikim         ###   ########.fr       */
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
	else
		return (-1);
}

static	int	command_finder2(char *command)
{
	if (!ft_strncmp(command, "/bin/", ft_strlen("/bin/")))
		return (2);
	else
		return (-1);
}

int	parsing(i)
{
	pid_t	execve_pid;//
	int		status;//
	int		rtn;//

	g_data.argv = ft_split(g_data.s_input[i], ' ');
	rtn = command_finder(g_data.argv[0]);
	if (rtn < 0)
		rtn = command_finder2(g_data.argv[0]);
	if (rtn == 2)
	{
		execve_pid = fork(); // fork
		if (execve_pid < 0)
			exit(EXIT_FAILURE);
		else if (execve_pid == 0) // 자식
		{
			free(g_data.argv);
			if (execve(g_data.argv[0], g_data.argv, g_data.env) == -1) //// envv?
			{
				printf("minishell: %s: No such file or directory\n", g_data.argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else // 부모
		{	
			waitpid(execve_pid, &status, 0);
			add_history(g_data.s_input[i]);
		}
		return (rtn);
	}
	else
		return (rtn);
}
