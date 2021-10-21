/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2021/10/21 15:08:16 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_prompt(int interrupt)
{
	if (interrupt == TRUE)
	{
		ft_putstr_fd("\b\b  ", 1);
	}
	ft_putstr_fd("\n$> ", 1);
}

int main(void)
{
	g_data.parent_pid = getpid();

	g_sigact.sa_flags = SA_SIGINFO;
	if (getpid() == g_data.parent_pid)
		g_sigact.sa_sigaction = interrupt_handler;
	else
		g_sigact.sa_sigaction = interrupt_handler_child;
	sigemptyset(&g_sigact.sa_mask);
	sigaction(SIGINT, &g_sigact, NULL);
	sigaction(SIGTSTP, &g_sigact, NULL);
	sigaction(SIGUSR1, &g_sigact, NULL);
	sigaction(SIGUSR2, &g_sigact, NULL);
	
	if (getpid() == g_data.parent_pid)
		ft_put_prompt(FALSE);

	g_data.child_pid = fork();

	// while (1)
	// {
	// 	pause();
	// }
	while (get_next_line(0, &g_data.msg) != 0)
	{
		// ft_putstr_fd(g_data.msg, 1);
		// free(g_data.msg);
		ft_put_prompt(FALSE);
		pause();
	}
}