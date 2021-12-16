/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:06:17 by bahn              #+#    #+#             */
/*   Updated: 2021/12/16 17:39:47 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putendl_fd(NULL, 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
		ft_putstr_fd("\b \b\b \b", 0);
}
