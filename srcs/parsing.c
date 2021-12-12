/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/12 03:01:09 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	command_finder(char *command)
{
	if (!ft_strncmp(command, "echo", ft_strlen(command)))
		return (double_quotation());
	else if (!ft_strncmp(command, "cd", ft_strlen(command)))
		return (change_dir());
	else if (!ft_strncmp(command, "pwd", ft_strlen(command)))
		return (0);
	else if (!ft_strncmp(command, "export", ft_strlen(command)))
		return (0);
	else if (!ft_strncmp(command, "unset", ft_strlen(command)))
		return (0);
	else if (!ft_strncmp(command, "env", ft_strlen(command)))
		return (0);
	else if (!ft_strncmp(command, "exit", ft_strlen(command)))
		return (0);
	else
		return (1);
}

int	parsing(void)
{
	pid_t	execve_pid;
	int		status;
	char	*cmd_path;
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
			cmd_path = ft_strjoin("/bin/", g_data.argv[0]);
			if (execve(cmd_path, g_data.argv, g_data.env) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{	
			waitpid(execve_pid, &status, 0);
			// printf("%s\n", g_data.input);
			//// execve 함수 호출 후 g_data.input 데이터가 사라짐
			//// execve의 출력문에 의해 사라지는건가?
			// add_history(g_data.input);
		}
		free(cmd_path);
		return (0);
	}
	else if (rtn < 0)
		return (0);
	else
		return (1);
}
