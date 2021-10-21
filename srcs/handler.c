/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:06:17 by bahn              #+#    #+#             */
/*   Updated: 2021/10/21 15:08:41 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt_handler(int signo, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (signo == SIGINT)
	{
		ft_put_prompt(TRUE);
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

void	interrupt_handler_child(int signo, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (signo == SIGINT)
	{
		kill(g_data.parent_pid, signo);
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