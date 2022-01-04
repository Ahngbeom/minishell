/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:06:17 by bahn              #+#    #+#             */
/*   Updated: 2022/01/04 13:47:09 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putendl_fd("\b \b\b \b", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
		ft_putstr_fd("\b \b\b \b", 0);
}

	//	ioctl 함수를 통해 EscapeSequence 해결?
	// if (tcgetattr(STDIN_FILENO, &g_data.termios))
		// exit(EXIT_FAILURE);
	// g_data.termios.c_lflag = ICANON | ~ECHO;
	// g_data.termios.c_cc[VMIN] = 1;
	// g_data.termios.c_cc[VTIME] = 0;
	// if (tcsetattr(STDIN_FILENO, TCSANOW, &g_data.termios))
		// exit(EXIT_FAILURE);