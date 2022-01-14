/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2022/01/14 15:30:41 by bahn             ###   ########.fr       */
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

void	parsing(int fd[], t_command *command)
{
	pid_t	pid;
	int		stat_loc;
	int		org_fd;

	org_fd = dup(STDOUT_FILENO);
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		fd[WRITE] = open("output", O_CREAT | O_RDWR, S_IRWXU);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		close(fd[READ]);
		command_finder(command);
		if (command->builtin_func != NULL)
			exit(command->builtin_func(command));
		else
			exit(to_execve(command));
	}
	else
	{
		// if (!ft_strncmp(command->type, PIPE, ft_strlen(command->type) + 1))
		// {
		// 	dup2(fd[WRITE], fd[READ]);
		// }
		// else if (!ft_strncmp(command->type, TRNC_REDIR, ft_strlen(command->type)))
		// {
		// 	fd[READ] = open("output", O_RDONLY | O_TRUNC, S_IRWXU);
		// }
		// else if (!ft_strncmp(command->type, APND_REDIR, ft_strlen(command->type)))
		// {  
		// 	fd[READ] = open("output", O_RDONLY | O_APPEND, S_IRWXU);
		// }
		// else
		// 	fd[READ] = open("output", O_RDONLY | O_TRUNC, S_IRWXU);
		fd[READ] = open("output", O_RDONLY | O_TRUNC, S_IRWXU);
		dup2(fd[READ], STDIN_FILENO);
		waitpid(pid, &stat_loc, 0);
		dup2(org_fd, STDOUT_FILENO);
		close(fd[WRITE]);
	}
}
