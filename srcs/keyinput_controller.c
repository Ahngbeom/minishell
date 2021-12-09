/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyinput_controller.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:24:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/09 17:02:57 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	keyinput_controller(void)
{
	g_data.log->ch = 0;
	g_data.log->index = -1;
	while (read(STDIN_FILENO, &g_data.log->ch, 1) > 0)
	{
		if (g_data.log->ch == EOT)
		{
			if (g_data.log->index == -1)
				return (1);
			else
				continue ;
		}
		else if (g_data.log->ch == 127)
		{
			if (g_data.log->index >= 0)
			{
				--g_data.log->index;
				write(0, "\b \b", 3);
			}
		}
		else if (g_data.log->ch == LF)
		{
			break ;
		}
		else
		{
			++g_data.log->index;
			write(0, &g_data.log->ch, 1);
		}
		g_data.log->ch = 0;
	}
	return (0);
}
