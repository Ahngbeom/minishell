/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:04:38 by bahn              #+#    #+#             */
/*   Updated: 2021/12/09 01:06:41 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # define _XOPEN_SOURCE 500		// sigaction

# include <unistd.h>			//
# include <signal.h>			// sigaction
# include <stdio.h>				// printf()
# include <readline/readline.h> // readline()
# include <readline/history.h>	// add_history
# include <termios.h> 			// tcgetattr()
# include <sys/wait.h>			// wait(), waitpid(), wait3(), wait4()

# include "libft.h"
# include "get_next_line.h"

# define EOT 4
# define LF	10

// struct sigaction		g_sigact;
typedef struct termios		t_termios;
typedef struct s_data		t_data;
typedef struct s_log		t_log;

struct s_data
{
	pid_t		pid;
	t_termios	org_term;
	t_termios	msh_term;
	char		**env;
	char		*input;

	t_log		*log;
};

struct s_log
{
	int	ch;
	int	sigint;
};

void	ft_put_prompt(int interrupt);

void	interrupt_handler(int signo, siginfo_t *siginfo, void *context);
void	interrupt_handler_child(int signo, siginfo_t *siginfo, void *context);

#endif