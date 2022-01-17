/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:57:58 by bahn              #+#    #+#             */
/*   Updated: 2022/01/17 17:24:34 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_redirection(t_list **list, int *fd, char *redirect)
{
	int			file;
	t_command	*cmd;
	char		buf[BUFSIZ];

	*list = (*list)->next;
	cmd = (*list)->content;
	if (!ft_strncmp(redirect, TRNC_REDIR, ft_strlen(redirect) + 1))
		file = open(cmd->argv[0], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	else if (!ft_strncmp(redirect, APND_REDIR, ft_strlen(redirect) + 1))
	{
		file = open(cmd->argv[0], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	}
	// else if (!ft_strncmp(redirect, R_TRNC_REDIR, ft_strlen(redirect)))
	// 	file = open(cmd->argv[0], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	// else if (!ft_strncmp(redirect, R_APND_REDIR, ft_strlen(redirect)))
	// 	file = open(cmd->argv[0], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	while (read(*fd, buf, BUFSIZ) > 0)
	{
		write(file, buf, ft_strlen(buf));
		ft_bzero(buf, ft_strlen(buf));
	}
	close(*fd);
	*fd = file;
	*list = (*list)->next;
}
