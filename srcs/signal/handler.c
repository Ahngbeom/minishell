/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:06:17 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 20:25:16 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_quit(int signo, pid_t pid)
{
	if (signo == SIGQUIT)
	{
		if (pid == WAIT_ANY)
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			exit_status_switch(131);
			ft_putendl_fd("Quit: 3", 1);
		}
	}
}

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
		else
		{	
			exit_status_switch(130);
			ft_putchar_fd(LF, 1);
		}
	}
	sig_quit(signo, pid);
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
