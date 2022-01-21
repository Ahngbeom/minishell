/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:52:01 by bahn              #+#    #+#             */
/*   Updated: 2022/01/21 11:50:43 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structures.h"

// pipe
void	if_pipe(t_list *list, int **fd, int i);
t_list	*ft_pipe(t_list *list);

// void	prompt(void);
char	*prompt(void);

// Key Interrupt Handler
void	set_termios(void);
void	signal_handler(int signo);

// History
void	set_history(t_list *lst_env);

// Parsing
void	input_split(t_list **list, char *input);
void	split_2_command(t_list **list, char *input);
void	abbreviation_converter(t_list *list);

// Starting to Minishell
int		minishell(void);

// Set & Release PIPE (for Built-In ?)
void	set_pipe(t_pipe *data);
int		release_pipe(t_pipe *data);

// Create PIPE for execve & Run execve(path, argv, envv);
int		execution(t_command *command, int input_fd);
char	**envp_to_arr_converter(t_list *list);
int	to_execve(t_command *command);
int		to_execve_2(t_command *command);
// int		to_execve_3(t_command *command);

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
t_list	*set_lstenvv(char *env[]);
int		envv_name_format_checker(char *key);
void	envmark_converter(char **arg);
void	update_envv(char *key, char *new_value);

// Redirection
void	minishell_redirection(t_list **list, int *fd, char *redirect);

// Arguments Vector Utils
int		argv_counter(char *argv[]);
size_t	arg_finder(t_command *cmd, char *input);
char	**add_arguments(char **argv, char *add);

// Other Utils
void	set_redirection(void);

char	*more_input(char *input);
int		get_next_line(int fd, char **line);

char	*execfile_finder(char *command);
int		redirection_finder(char *redirection[], char *input, char **save);

void	backslash_converter(char **arg);

char	*remove_enclosed_quotes(char *arg);
char	*escape_sequence(char *arg);

int		incorrect_exit(t_command *command);

char	*ft_strjoin_with_free(char *str1, char *str2);

void	print_info(t_list *list, int on_off);

// Free Memory
void	minishell_finalize(void);
void	hash_free(void *ptr);
void	split_free(char **split);
void	command_free(void *command);

#endif