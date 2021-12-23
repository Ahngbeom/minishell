/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:52:01 by bahn              #+#    #+#             */
/*   Updated: 2021/12/23 22:59:28 by bahn             ###   ########.fr       */
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
void	parsing(t_list *commands);

// Quotes
int		then_input(int index, char start_quotes);
char	quotes_counter(char *str);

// COMMAND echo
int		minishell_echo(t_command *command);

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

// Environment Variable Utils
char	*envv_getvalue(char *key);
int		envvar_checker(void);
t_list	**set_lstenv(char *env[]);
int		envv_name_format_checker(char *key);

// Free Memory
void	minishell_finalize(void);
void	split_free(char **split);
void	command_free(void *command);

// Other Utils
void	ft_split_command(t_list **list, char *s, char **redirect);
char	*remove_enclosed_quotes(char *argv);
int		incorrect_exit(t_command *command);

#endif