/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/25 16:24:16 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	command_finder(t_command *command)
{
	if (!ft_strncmp(command->argv[0], "echo", ft_strlen("echo") + 1))
		// command->func = minishell_echo;
		command->func = minishell_echo_for_execve;
	else if (!ft_strncmp(command->argv[0], "cd", ft_strlen("cd") + 1))
		command->func = minishell_cd;
	else if (!ft_strncmp(command->argv[0], "pwd", ft_strlen("pwd") + 1))
		command->func = minishell_pwd;
	else if (!ft_strncmp(command->argv[0], "export", ft_strlen("export") + 1))
		command->func = minishell_export;
	else if (!ft_strncmp(command->argv[0], "unset", ft_strlen("unset") + 1))
		command->func = minishell_unset;
	else if (!ft_strncmp(command->argv[0], "env", ft_strlen("env") + 1))
		command->func = minishell_env;
	else if (!ft_strncmp(command->argv[0], "exit", ft_strlen("env") + 1))
		command->func = incorrect_exit;
	else if (!ft_strncmp(command->argv[0], "$?", ft_strlen("$?") + 1))
		// command->func = minishell_exit_status;
		command->func = NULL;
	else
		command->func = NULL;
}

void	parsing(t_command *command)
{
	command_finder(command);
	if (command->func != NULL)
		command->func(command);
}
	
