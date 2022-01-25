/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 16:55:58 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_execve_2(t_command *command)
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = execfile_finder(command->argv[0]);
	if (cmd_path == NULL)
		exit(127);
	if (execve(cmd_path, command->argv, NULL) == -1)
		exit(errno);
	exit(EXIT_SUCCESS);
}

static void	to_execve(t_pipe *pipe_data, \
						char *cmd_path, char **argv, \
							int input_fd)
{
	char	**envp;

	close(pipe_data->fd[READ]);
	close(pipe_data->fd[WRITE]);
	if (cmd_path == NULL)
		exit(127);
	if (input_fd != -1)
		dup2(input_fd, STDIN_FILENO);
	envp = envp_to_arr_converter(g_data.lst_env);
	if (execve(cmd_path, argv, envp) == -1)
		exit(errno);
}

int	execution(t_command *command, int input_fd)
{
	t_pipe	pipe_data;
	pid_t	pid;
	int		status;
	char	*cmd_path;

	cmd_path = execfile_finder(command->argv[0]);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		to_execve(&pipe_data, cmd_path, command->argv, input_fd);
	status = 0;
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 127)
		printf("minishell: %s: command not found\n", command->argv[0]);
	exit_status_switch(WEXITSTATUS(status));
	if (input_fd != -1)
		close(input_fd);
	if (cmd_path != NULL)
		free(cmd_path);
	return (release_pipe(&pipe_data));
}
