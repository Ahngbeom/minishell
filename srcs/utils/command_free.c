/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:58:22 by bahn              #+#    #+#             */
/*   Updated: 2022/01/10 20:05:34 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(void *command)
{
	((t_command *)command)->func = NULL;
	split_free(((t_command *)command)->argv);
	((t_command *)command)->argv = NULL;
	// if (((t_command *)command)->output)
	// 	free(((t_command *)command)->output);
}
