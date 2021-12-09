/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2021/12/09 17:44:45 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

int	minishell(void)
{
	signal(SIGINT, signal_handler);
	g_data.log = malloc(sizeof(t_log));
	g_data.log->sigint = 0;
	g_data.input = readline(prompt());
	if (g_data.input != NULL)
	{
		ft_putendl_fd(g_data.input, 1);
		if (!g_data.log->sigint)
			add_history(g_data.input);
		free(g_data.input);
		return (0);
	}
	ft_putendl_fd("exit", 1);
	return (1);
}
