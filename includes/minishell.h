/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:04:38 by bahn              #+#    #+#             */
/*   Updated: 2021/12/21 15:24:43 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define EXEC_PROC 0
# define SELF_PROC 1

# define BIN_PATH "/bin/"

typedef struct termios		t_termios;
typedef struct s_data		t_data;
typedef struct s_hash		t_hash;

extern t_data				g_data;

t_data						g_data;

struct s_data
{
	pid_t		pid;

	char		*prompt;
	char		**argv;
	char		**org_env;
	t_list		**envv;

	char		*home_path;
	char		*cmd_path;

	char		*current_path;

	char		*input;
	char		**split_input;
};

struct s_hash
{
	char	*key;
	char	*value;
};

// void	prompt(void);
char	*prompt(void);

// Key Interrupt Handler
void	signal_handler(int signo);

// Arguments Vector
int		argv_counter(char *argv[]);

// Environment Variable
int		envvar_checker(void);
t_list	**set_env(char *env[]);
void	free_env(char *env[]);

int		minishell_run();
int		minishell(void);

void	parsing(char *str);

// Quotes
int		then_input(int index, char start_quotes);
char	quotes_counter(char *str);

// echo
int		minishell_echo(void);
int		minishell_echo_for_execve(void);

// cd
int		minishell_cd(void);
int		change_dir(void); // Not used now

// pwd
int		minishell_pwd(void);

// export
int		minishell_export(void);

// unset
int		minishell_unset(void);

// env
int		minishell_env(void);
char	*env_getvalue(char *key);
void	env_chararr_converter(void);

// Utils
void	split_free(char **split);

#endif