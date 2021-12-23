/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:04:38 by bahn              #+#    #+#             */
/*   Updated: 2021/12/23 15:55:08 by bahn             ###   ########.fr       */
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
typedef struct s_command	t_command;

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

	char		*input;
	// char		**split_input;

	char		**arr_redirect;

	t_command	**command;
	t_list		*command2;

	char		*output;
	
	int			*pipe;
};

struct s_hash
{
	char	*key;
	char	*value;
};

struct s_command
{
	int			(*func)(t_command *);

	char		**argv;
	char		*redirect;
	
	// char		*input;
	// char		**split_input;

};


// void	prompt(void);
char	*prompt(void);

// Key Interrupt Handler
void	signal_handler(int signo);

// Arguments Vector
int		argv_counter(char *argv[]);

// Environment Variable
int		envvar_checker(void);
t_list	**set_lstenv(char *env[]);

int		minishell_run();
int		minishell(void);

void	parsing(t_list *commands);

// Quotes
int		then_input(int index, char start_quotes);
char	quotes_counter(char *str);

// echo
int		minishell_echo(t_command *command);

// cd
int		minishell_cd(t_command *command);

// pwd
int		minishell_pwd(t_command *command);

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
void	command_free(void *command);

void	ft_split_command(t_list **list, char *s, char **redirect);

char	*remove_enclosed_quotes(char *argv);

#endif