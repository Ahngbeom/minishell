/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2022/01/17 01:09:17 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	command_finder(t_command *command)
{
	if (!ft_strncmp(command->argv[0], "echo", ft_strlen("echo") + 1))
		command->builtin_func = minishell_echo;
	else if (!ft_strncmp(command->argv[0], "cd", ft_strlen("cd") + 1))
		command->builtin_func = minishell_cd;
	else if (!ft_strncmp(command->argv[0], "pwd", ft_strlen("pwd") + 1))
		command->builtin_func = minishell_pwd;
	else if (!ft_strncmp(command->argv[0], "export", ft_strlen("export") + 1))
		command->builtin_func = minishell_export;
	else if (!ft_strncmp(command->argv[0], "unset", ft_strlen("unset") + 1))
		command->builtin_func = minishell_unset;
	else if (!ft_strncmp(command->argv[0], "env", ft_strlen("env") + 1))
		command->builtin_func = minishell_env;
	else if (!ft_strncmp(command->argv[0], "exit", ft_strlen("exit") + 1))
		command->builtin_func = incorrect_exit;
	else
		command->builtin_func = NULL;
}

void	parsing(t_command *command)
{
	pid_t	pid;
	int		fd[2];
	int		stat_loc;
	int		org_stdin;
	int		org_stdout;

	org_stdin = dup(STDIN_FILENO);
	org_stdout = dup(STDOUT_FILENO);
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		if (command->o_flag == 0)
			fd[WRITE] = open(g_data.output, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		else
			fd[WRITE] = open(g_data.output, command->o_flag, S_IRWXU);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		close(fd[READ]);
		command_finder(command);
		if (command->builtin_func != NULL)
			exit(command->builtin_func(command));
		else
			exit(to_execve(command));
	}
	close(fd[READ]);
	close(fd[WRITE]);
	waitpid(pid, &stat_loc, 0);
	dup2(org_stdin, STDIN_FILENO);
	dup2(org_stdout, STDOUT_FILENO);
}
