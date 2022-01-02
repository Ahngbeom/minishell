/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:58:22 by bahn              #+#    #+#             */
/*   Updated: 2022/01/02 17:37:09 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(void *command)
{
	split_free(((t_command *)command)->argv);
	if (((t_command *)command)->output)
		free(((t_command *)command)->output);
}
