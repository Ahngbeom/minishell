/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:58:22 by bahn              #+#    #+#             */
/*   Updated: 2022/01/19 16:50:45 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(void *content)
{
	t_command	*cmd;

	cmd = content;
	cmd->builtin_func = NULL;
	split_free(cmd->argv);
	cmd->argv = NULL;
	cmd->type = NULL;
	free(cmd);
	cmd = NULL;
}
