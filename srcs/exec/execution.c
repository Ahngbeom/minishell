/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2022/01/19 16:59:13 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	to_execve(t_pipe *pipe_data, \
						char *cmd_path, char **argv, char **envp, \
							int input_fd)
{
	close(pipe_data->fd[READ]);
	close(pipe_data->fd[WRITE]);
	if (cmd_path == NULL)
		exit(127);
	if (input_fd != -1)
		dup2(input_fd, STDIN_FILENO);
	if (execve(cmd_path, argv, envp) == -1)
		exit(errno);
}

int	execution(t_command *command, int input_fd)
{
	t_pipe	pipe_data;
	pid_t	pid;
	int		status;
	char	*cmd_path;
	char	**envp;

	set_pipe(&pipe_data);
	cmd_path = execfile_finder(command->argv[0]);
	envp = envp_to_arr_converter(g_data.lst_env);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		to_execve(&pipe_data, cmd_path, command->argv, envp, input_fd);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 127)
		printf("minishell: %s: command not found\n", command->argv[0]);
	if (g_data.exit_stat != NULL)
		free(g_data.exit_stat);
	g_data.exit_stat = ft_itoa(WEXITSTATUS(status));
	if (input_fd != -1)
		close(input_fd);
	if (cmd_path != NULL)
		free(cmd_path);
	if (envp != NULL)
		split_free(envp);
	return (release_pipe(&pipe_data));
}
