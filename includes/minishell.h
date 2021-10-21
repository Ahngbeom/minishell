/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:04:38 by bahn              #+#    #+#             */
/*   Updated: 2021/10/21 15:08:15 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 500

# define TRUE 1
# define FALSE 0

# include <unistd.h>
# include <signal.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>

struct sigaction	g_sigact;

typedef struct s_data t_data;

struct s_data
{
	pid_t	parent_pid;
	pid_t	child_pid;
	char	*msg;
};

t_data g_data;

void	ft_put_prompt(int interrupt);

void	interrupt_handler(int signo, siginfo_t *siginfo, void *context);
void	interrupt_handler_child(int signo, siginfo_t *siginfo, void *context);


#endif