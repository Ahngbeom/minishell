/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/23 15:52:07 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	command_finder(t_command *command)
{
	if (!ft_strncmp(command->argv[0], "echo", ft_strlen("echo") + 1))
		command->func = minishell_echo;
	else if (!ft_strncmp(command->argv[0], "cd", ft_strlen("cd") + 1))
		command->func = minishell_cd;
	else if (!ft_strncmp(command->argv[0], "pwd", ft_strlen("pwd") + 1))
		command->func = minishell_pwd;
	else if (!ft_strncmp(command->argv[0], "export", ft_strlen("export") + 1))
		command->func = NULL; //minishell_export;
	else if (!ft_strncmp(command->argv[0], "unset", ft_strlen("unset") + 1))
		command->func = NULL; //minishell_unset;
	else if (!ft_strncmp(command->argv[0], "env", ft_strlen("env") + 1))
		command->func = NULL; //minishell_env;
	else
		command->func = NULL;
}

void	parsing(t_list *commands)
{
	t_command	*command;
	char		*cmd_path;
	pid_t		execve_pid;
	int			status;

	command = commands->content;
	command_finder(command);
	if (command->func == NULL)
	{
		execve_pid = fork();
		if (execve_pid < 0)
			exit(EXIT_FAILURE);
		else if (execve_pid == 0)
		{
			cmd_path = ft_strjoin(BIN_PATH, command->argv[0]);
			if (execve(cmd_path, command->argv, NULL) == -1) // execve 에서 envp는 NULL?
			{
				printf("bash: %s: command not found\n", command->argv[0]);
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
	else
		command->func(command);
}
	
