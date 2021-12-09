/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:06:17 by bahn              #+#    #+#             */
/*   Updated: 2021/12/09 17:50:29 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_data.log->sigint = 1;
		// if (g_data.input != NULL)
		// 	free(g_data.input);
		write(STDOUT_FILENO, "^C\n", 3);
		
		write(1, prompt(), ft_strlen(prompt()));
	}
}
