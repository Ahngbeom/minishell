/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2021/10/20 23:20:06 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data g_data;

void	interrupt_handler(int signo, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (signo == SIGINT)
	{
		ft_putstr_fd("\b\b  \n$> ", 1);
	}
	else if (signo == SIGTSTP)
	{
		ft_putstr_fd("\b\bSIGTSTP(Ctrl + z)\n", 1);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_putendl_fd("CONNECTION FAILED", 1);
		exit(EXIT_FAILURE);
	}
}

int main(void)
{
	g_sigact.sa_flags = SA_SIGINFO;
	g_sigact.sa_sigaction = interrupt_handler;
	sigemptyset(&g_sigact.sa_mask);
	sigaction(SIGINT, &g_sigact, NULL);
	sigaction(SIGTSTP, &g_sigact, NULL);
	sigaction(SIGUSR1, &g_sigact, NULL);
	// sigaction(SIGUSR2, &g_sigact, NULL);
	
	g_data.pid = getpid();

	ft_putstr_fd("Welcome MINISHELL ! (PID : ", 1);
	ft_putnbr_fd(g_data.pid, 1);
	ft_putstr_fd(")\n$> ", 1);

	while (1)
	{
		if (get_next_line(0, &g_data.msg) != 0)
		{
			ft_putendl_fd(g_data.msg, 1);/* code */
		}
		else
			pause();
	}
}