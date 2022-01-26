/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 19:56:18 by minsikim         ###   ########.fr       */
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
		command->builtin_func = minishell_exit;
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

void	do_minishell(t_list **list, t_command **cmd, int *fd)
{
	if ((*cmd)->builtin_func != NULL)
		*fd = (*cmd)->builtin_func(*cmd);
	else
		*fd = execution(*cmd, *fd);
	if ((*cmd)->type == NULL || \
		!ft_strncmp((*cmd)->type, SEMI_COLON, ft_strlen((*cmd)->type) + 1))
		print_result(list, fd);
	else if (!ft_strncmp((*cmd)->type, PIPE, ft_strlen((*cmd)->type) + 1))
		*list = (*list)->next;
	else
		minishell_redirection(list, fd, (*cmd)->type);
	g_data.envv_path = set_envvpath();
}

int	minishell(void)
{
	t_list		*list;
	t_command	*cmd;
	int			fd;

	fd = -1;
	set_flag(g_data.lst_cmds);
	list = g_data.lst_cmds;
	while (list != NULL)
	{
		cmd = list->content;
		command_finder(cmd);
		if (cmd->next_flag)
		{
			list = ft_pipe(list);
			break ;
		}
		do_minishell(&list, &cmd, &fd);
	}
	ft_lstclear(&g_data.lst_cmds, command_free);
	return (0);
}
