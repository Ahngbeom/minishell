/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:57:58 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 02:54:18 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_type_checker(char *type)
{
	if (type == NULL)
		return (0);
	else if (!ft_strncmp(type, TRNC_REDIR, ft_strlen(type) + 1) || \
				!ft_strncmp(type, APND_REDIR, ft_strlen(type) + 1))
	{
		return (1);
	}
	else
		return (0);
}

void	minishell_redirection(t_list **cmd_ptr, int *fd, char *redirect)
{
	int			file;
	t_command	*cmd;
	char		buf[BUFSIZ];

	*cmd_ptr = (*cmd_ptr)->next;
	cmd = (*cmd_ptr)->content;
	if (!ft_strncmp(redirect, TRNC_REDIR, ft_strlen(redirect) + 1))
		file = open(cmd->argv[0], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	else if (!ft_strncmp(redirect, APND_REDIR, ft_strlen(redirect) + 1))
		file = open(cmd->argv[0], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	if ((*cmd_ptr)->next != NULL && redir_type_checker(cmd->type))
		minishell_redirection(cmd_ptr, fd, cmd->type);
	else
	{
		ft_bzero(buf, BUFSIZ);
		while (read(*fd, buf, BUFSIZ) > 0)
		{
			write(file, buf, ft_strlen(buf));
			ft_bzero(buf, ft_strlen(buf));
		}
	}
	close(*fd);
	*fd = -1;
	*cmd_ptr = (*cmd_ptr)->next;
}

void	minishell_r_redirection(t_list **cmd_ptr, char *type, t_pipe *pipe_data, int *flag)
{
	struct stat	stat_buf;
	t_command	*cmd;
	int			fd;
	char		buf[BUFSIZ];

	*cmd_ptr = (*cmd_ptr)->next;
	cmd = (*cmd_ptr)->content;
	if (!ft_strncmp(type, R_TRNC_REDIR, ft_strlen(type) + 1))
	{
		if (lstat(cmd->argv[0], &stat_buf) == 0)
		{
			fd = open(cmd->argv[0], O_RDWR, S_IRWXU);
			ft_bzero(buf, BUFSIZ);
			while (read(fd, buf, BUFSIZ) > 0)
			{
				write(pipe_data->fd[READ], buf, ft_strlen(buf));
				ft_bzero(buf, ft_strlen(buf));
			}
			ft_putendl_fd("?", pipe_data->org_stdioe[WRITE]);
			*cmd_ptr = (*cmd_ptr)->next->next;
		}
		else
		{
			ft_putstr_fd("minishell: ", pipe_data->org_stdioe[WRITE]);
			ft_putstr_fd(cmd->argv[0], pipe_data->org_stdioe[WRITE]);
			ft_putendl_fd(": No such file or directory", pipe_data->org_stdioe[WRITE]);
		}
	}
	*flag = 1;
	// else if (!ft_strncmp(redirect, R_APND_REDIR, ft_strlen(redirect) + 1))
	// {
		
	// }
	
	// if ((*cmd_ptr)->next != NULL && redir_type_checker(cmd->type))
	// 	minishell_redirection(cmd_ptr, fd, cmd->type);
	// else
	// {
	// 	ft_bzero(buf, BUFSIZ);
	// 	while (read(*fd, buf, BUFSIZ) > 0)
	// 	{
	// 		write(file, buf, ft_strlen(buf));
	// 		ft_bzero(buf, ft_strlen(buf));
	// 	}
	// }
	// close(*fd);
	// *fd = -1;
	// *cmd_ptr = (*cmd_ptr)->next;
}
