/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:06:17 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 13:59:28 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (signo == SIGINT)
	{
		if (pid == WAIT_ANY)
		{
			ft_putchar_fd(LF, 1);
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
		}
	}
}

void	set_termios(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term))
		exit(EXIT_FAILURE);
	term.c_lflag &= ~(ECHOCTL);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term))
		exit(EXIT_FAILURE);
}
