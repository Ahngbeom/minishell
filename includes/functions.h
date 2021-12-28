/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:52:01 by bahn              #+#    #+#             */
/*   Updated: 2021/12/28 12:10:42 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structures.h"

// void	prompt(void);
char	*prompt(void);

// Key Interrupt Handler
void	signal_handler(int signo);

// Arguments Vector Utils
int		argv_counter(char *argv[]);

// Start to Minishell
int		minishell(void);

// Parsing for Input
void	parsing(t_command *command);

// Run execve(path, argv, envv);
int		to_execve(t_command *command);

// COMMAND echo
int		minishell_echo(t_command *command);
int		minishell_echo_for_execve(t_command *command);

// COMMAND cd
int		minishell_cd(t_command *command);

// COMMAND pwd
int		minishell_pwd(t_command *command);

// COMMAND export
int		minishell_export(t_command *command);

// COMMAND unset
int		minishell_unset(t_command *command);

// COMMAND env
int		minishell_env(t_command *command);

// COMMAND $?
int		minishell_exit_status(t_command *command);

// Environment Variable Utils
char	*envv_getvalue(char *key);
int		envvar_checker(void);
t_list	**set_lstenv(char *env[]);
char	*envv_name_format_checker(char *key);

// Free Memory
void	minishell_finalize(void);
void	split_free(char **split);
void	command_free(void *command);

// Other Utils
char	*execfile_finder(char *command);

void	ft_split_command(t_list **list, char *s, char **redirect);

char	*remove_enclosed_quotes(char *argv);
char	*escape_sequence(char *arg);

int		incorrect_exit(t_command *command);

#endif