/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:04:38 by bahn              #+#    #+#             */
/*   Updated: 2021/12/15 16:00:25 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # define _XOPEN_SOURCE 500		// sigaction

# include <unistd.h>			// fork()
# include <signal.h>			// sigaction
# include <stdio.h>				// printf()
# include <readline/readline.h> // readline()
# include <readline/history.h>	// add_history
# include <termios.h> 			// tcgetattr()
# include <sys/wait.h>			// wait(), waitpid(), wait3(), wait4()
# include <fcntl.h>				// open()
# include <sys/stat.h>			// stat()
# include <errno.h>				// errno
# include "libft.h"

# define EOT 4
# define LF	10

// # define CMD_ECHO "echo"
// # define CMD_CD "cd"
// # define CMD_PWD "pwd"
// # define CMD_EXPORT "export"
// # define CMD_UNSET "unset"
// # define CMD_ENV "env"
// # define CMD_EXIT "exit"

# define SELF_PROCESSING 1

// struct sigaction		g_sigact;
typedef struct termios		t_termios;
typedef struct s_data		t_data;
typedef struct s_log		t_log;

extern t_data				g_data;

t_data						g_data;

struct s_data
{
	pid_t		pid;

	char		*prompt;
	char		**argv;
	char		**env;

	char		*home_path;
	char		*bin_path;
	char		*cmd_path;

	char		*pwd;

	char		*input;
};

struct s_log
{
	int	index;
	int	ch;
	int	sigint;
};

// void	prompt(void);
char	*prompt(void);

void	signal_handler(int signo);

// Arguments Vector
int		argv_counter(char *argv[]);

// Environment Variable
int		envvar_checker(void);
char	**set_env(int argc, char *argv[], char *env[]);
void	free_env(char *env[]);

int		minishell(void);

int		parsing(void);

int		change_dir(void);

// Quotes
int		then_input(int index, char start_quotes);

// echo
int		minishell_echo(void);
int		minishell_echo_for_execve(void);

// cd
int	minishell_cd(void);

#endif