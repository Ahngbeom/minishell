/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:34:57 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 22:55:46 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_error(t_pipe *pipe_data, \
						char *command, char *target, char *message)
{
	ft_putstr_fd("minishell: ", pipe_data->org_stdioe[STDOUT_FILENO]);
	ft_putstr_fd(command, pipe_data->org_stdioe[STDOUT_FILENO]);
	ft_putstr_fd(": `", pipe_data->org_stdioe[STDOUT_FILENO]);
	ft_putstr_fd(target, pipe_data->org_stdioe[STDOUT_FILENO]);
	ft_putstr_fd("\': ", pipe_data->org_stdioe[STDOUT_FILENO]);
	ft_putendl_fd(message, pipe_data->org_stdioe[STDOUT_FILENO]);
}
