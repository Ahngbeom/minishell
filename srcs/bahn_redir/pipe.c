/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:10:48 by bahn              #+#    #+#             */
/*   Updated: 2022/01/18 00:15:18 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipe(t_pipe *data)
{
	data->org_stdio[STDIN_FILENO] = dup(STDIN_FILENO);
	data->org_stdio[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (pipe(data->fd) == -1)
		exit(EXIT_FAILURE);
	dup2(data->fd[WRITE], STDOUT_FILENO);
}

int	release_pipe(t_pipe *data)
{
	close(data->fd[WRITE]);
	dup2(data->org_stdio[READ], STDIN_FILENO);
	dup2(data->org_stdio[WRITE], STDOUT_FILENO);
	return (data->fd[READ]);
}
