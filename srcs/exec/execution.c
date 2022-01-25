/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:33:53 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 14:30:01 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_execve(t_command *command)
{
	char	*cmd_path;
	char	**envp;
	pid_t	execve_pid;
	int		status;

	cmd_path = execfile_finder(command->argv[0]);
	envp = envp_to_arr_converter(g_data.lst_env);
	execve_pid = fork();
	if (execve_pid < 0)
		exit(EXIT_FAILURE);
	else if (execve_pid == 0)
	{
		if (cmd_path == NULL)
			exit(127);
		if (execve(cmd_path, command->argv, envp) == -1)
			exit(errno);
	}
	waitpid(execve_pid, &status, 0);
	if (WEXITSTATUS(status) == 127)
		printf("minishell: %s: command not found\n", command->argv[0]);
	free(g_data.exit_stat);
	g_data.exit_stat = ft_itoa(WEXITSTATUS(status));
	printf("status : %d\n", WEXITSTATUS(status));
	printf("exit status : %s\n", g_data.exit_stat);
	if (cmd_path != NULL)
		free(cmd_path);
	if (envp != NULL)
		split_free(envp);
	return (status);
}

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

static void	to_execve_bahn(t_pipe *pipe_data, \
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

int	execution(t_list **list, t_command *command, int input_fd, int *flag)
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
	{
		if (command->type && \
			(!ft_strncmp(command->type, R_TRNC_REDIR, ft_strlen(command->type) + 1) ||\
				!ft_strncmp(command->type, R_APND_REDIR, ft_strlen(command->type) + 1)))
		{
			minishell_r_redirection(list, command->type, &pipe_data, flag);
		}
		to_execve_bahn(&pipe_data, cmd_path, command->argv, envp, input_fd);
	}
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
