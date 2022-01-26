/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:10:48 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 12:39:20 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipe(t_pipe *data)
{
	data->org_stdioe[STDIN_FILENO] = dup(STDIN_FILENO);
	data->org_stdioe[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (pipe(data->fd) == -1)
		exit(EXIT_FAILURE);
	dup2(data->fd[WRITE], STDOUT_FILENO);
}

int	release_pipe(t_pipe *data)
{
	close(data->fd[WRITE]);
	dup2(data->org_stdioe[STDIN_FILENO], STDIN_FILENO);
	dup2(data->org_stdioe[STDOUT_FILENO], STDOUT_FILENO);
	close(data->org_stdioe[STDIN_FILENO]);
	close(data->org_stdioe[STDOUT_FILENO]);
	return (data->fd[READ]);
}
