/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:06:17 by bahn              #+#    #+#             */
/*   Updated: 2021/12/21 12:20:58 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	signal_handler(int signo)
{
	if (signo == SIGINT) // ctrl + C
	{
		ft_putendl_fd(NULL, 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (signo == SIGQUIT) // ctrl + "\"
		ft_putstr_fd("\b \b\b \b", 0);
	// if (signo == 15) // ctrl + D
	// {
	// 	printf("exit");
	// 	exit(0);
	// }
}
