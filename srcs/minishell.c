/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2022/01/18 20:01:39 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_flag(t_list *i_list)
{
	t_list	*list;
	t_command	*content;
	t_command	*next_con;

	list = i_list;
	while (list->next)
	{
		content = (t_command *)list->content;
		next_con = (t_command *)list->next->content;
		if (ft_strncmp(content->type, ";", 2) == 0)
		{
			content->next_flag = 1;
			next_con->pre_flag = 1;
		}
		if (ft_strncmp(content->type, "|", 2) == 0)
		{
			content->next_flag = 2;
			next_con->pre_flag = 2;
		}
		if (ft_strncmp(content->type, ">", 2) == 0)
		{
			content->next_flag = 3;
			next_con->pre_flag = 3;
		}
		if (ft_strncmp(content->type, ">>", 3) == 0)
		{
			content->next_flag = 4;
			next_con->pre_flag = 4;
		}
		list = list->next;
	}
}

void	ft_pipe(t_list	**list)
{
	int		**fd;
	int		i;
	int		size;
	t_command	*content;
	pid_t		pid;
	int			status;

	size = ft_lstsize(g_data.commands);
	fd = malloc(sizeof(int *) * size);
	i = -1;
	while (++i < size)
	{
		fd[i] = malloc(sizeof(int) * 2);
	}
	i = -1;
	while (++i < size && (*list)->content != NULL)
	{
		content = (*list)->content;
		pipe(fd[i]);
		pid = fork();
		if (pid == 0) // son
		{
			if (content->pre_flag == 2) // | argv
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
			}
			if (content->next_flag == 2) // argv |
			{
				dup2(fd[i][1], STDOUT_FILENO);
			}
			if (content->next_flag == 3) // argv >
			{
				fd[i][1] = open(((t_command *)(*list)->next->content)->argv[0], O_WRONLY | O_CREAT | O_TRUNC, 0644); // S_IROTH : 개인에게 읽기권한
				dup2(fd[i][1], STDOUT_FILENO);
				// close(fd[i][1]);
			}
			if (content->next_flag == 4) // argv >>
			{
				fd[i][1] = open(((t_command *)(*list)->next->content)->argv[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
				dup2(fd[i][1], STDOUT_FILENO);
			}
			to_execve_2((*list)->content);
		}
		else // parent
		{
			wait(&status);
			if (content->pre_flag == 2)
				close(fd[i - 1][0]);
			if (content->next_flag == 2)
				close(fd[i][1]);
			g_data.exit_stat = ft_itoa(WEXITSTATUS(status));
			if (WEXITSTATUS(status) == 127)
				printf("minishell: %s: command not found\n", ((t_command *)(*list)->content)->argv[0]);
		}
		if ((*list)->next)
			*list = (*list)->next;
	}
}

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

static void	print_result(t_list **list, int *fd)
{
	char	buf[BUFSIZ];

	ft_bzero(buf, BUFSIZ);
	while (read(*fd, buf, BUFSIZ) > 0)
	{
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_bzero(buf, ft_strlen(buf));
	}
	close(*fd);
	*fd = -1;
	*list = (*list)->next;
}

int	minishell(void)
{
	t_list		*list;
	t_command	*cmd;
	int			fd;

	fd = -1;
	list = g_data.commands;
	while (list != NULL)
	{
		cmd = list->content;
		command_finder(cmd);
		if (cmd->builtin_func != NULL)
			fd = cmd->builtin_func(cmd);
		else
			fd = execution(cmd, fd);
		if (cmd->type == NULL || \
			!ft_strncmp(cmd->type, SEMI_COLON, ft_strlen(cmd->type) + 1))
			print_result(&list, &fd);
		else if (!ft_strncmp(cmd->type, PIPE, ft_strlen(cmd->type) + 1))
			list = list->next;
		else
			minishell_redirection(&list, &fd, cmd->type);
		g_data.envv_path = set_envvpath();
	}
	if (fd < 0 || fd >= 3)
		close(fd);
	ft_lstclear(&g_data.commands, command_free);
	return (0);
}
