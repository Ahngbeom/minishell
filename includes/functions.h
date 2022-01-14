/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:52:01 by bahn              #+#    #+#             */
/*   Updated: 2022/01/13 22:07:25 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structures.h"

// void	prompt(void);
char	*prompt(void);

// Key Interrupt Handler
void	set_termios(void);
void	signal_handler(int signo);

// Arguments Vector Utils
int		argv_counter(char *argv[]);

// Start to Minishell
int		minishell(char **input);

// Parsing for Input
void	parsing(int fd[], t_command *command);

// Run execve(path, argv, envv);
char	**envp_to_arr_converter(t_list *list);
int		to_execve(t_command *command);
int		to_execve_2(t_command *command);
int		to_execve_3(t_command *command);

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
char	**set_envvpath(void);
t_hash	*get_envv(char *key);
char	*get_envv_value(char *key);
t_list	**set_lstenvv(char *env[]);
int		envv_name_format_checker(char *key);
char	*envv_converter(char *arg);

// Redirection Utils
void	set_redirection(void);

// Free Memory
void	minishell_finalize(void);
void	split_free(char **split);
void	command_free(void *command);

// Other Utils
char	*more_input(char *input);
int		get_next_line(int fd, char **line);

char	*execfile_finder(char *command);
int		redirection_finder(char *redirection[], char *input, char **save);
void	input_split(t_list **list, char *input);

size_t	arg_finder(t_command *cmd, char *input);

void	backslash_converter(char **arg);

char	*remove_enclosed_quotes(char *arg);
char	*escape_sequence(char *arg);

int		incorrect_exit(t_command *command);

char	*ft_strjoin_with_free(char *str1, char *str2);

#endif