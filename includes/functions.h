/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:52:01 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 19:19:59 by minsikim         ###   ########.fr       */
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
int		split_2_command(t_list **list, char *input);
size_t	command_extractor(char **input, char **splitted);
int		quote_finder(char **ptr, int *length, char **input);
char	*more_input(char *input);
char	*more_input2(char *input, char quotes);
char	*type_finder(char *str, int *length, char **input);
void	remove_quotes(t_command *command);
char	**quotes_split(char *s, char c);
void	set_type(t_command *command, char **sentence);
void	abbreviation_converter(t_list *list);

// Starting to Minishell
int		minishell(void);

// Set & Release PIPE (for Built-In ?)
void	set_pipe(t_pipe *data);
int		release_pipe(t_pipe *data);

// Create PIPE for execve & Run execve(path, argv, envv);
int		execution(t_command *command, int input_fd);
char	**envp_to_arr_converter(t_list *list);
int		to_execve_minsikim(t_command *command);
int		to_execve_2(t_command *command);
// int		to_execve_3(t_command *command);

//PIPE.c
void	set_pip(t_pip *pip, t_list *list);
void	free_fd(t_pip pip);
t_list	*ft_pipe(t_list *list);
void	set_flag(t_list *i_list);

void	if_pipe(t_list *list, int **fd, int i);
void	if_flag_right(t_list *list, t_command *exe, int **fd, int i);
void	if_flag_right_no_exe(t_list *list, int **fd, int i);
void	if_flag_left(t_list *list, t_command *exe, int **fd, int *i);
void	if_flag_d_left(t_list *list, t_command *exe, t_pip pip, int *i);
void	while_34(t_list **list);
void	while_3456(t_list **list, int *i);
void	do_son(t_list *list, t_pip pip);
void	do_son_2(t_list *list, t_pip pip, int *i, int out_fd);

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

// COMMAND exit with arguments
int		minishell_exit(t_command *command);

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
// size_t	arg_finder(t_command *cmd, char *input);
char	**add_arguments(char **argv, char *add);

// Other Utils
void	increase_shlvl(void);

void	minishell_error(t_pipe *pipe_data, \
						char *command, char *target, char *message);

int		exit_checker(char *input);
int		syntax_checker(char *input);

void	set_redirection(void);

void	add_command_to_list(t_list **list, t_command **command);

char	*execfile_finder(char *command);
int		redirection_finder(char *redirection[], char *input, char **save);

void	backslash_converter(char **arg);

char	*remove_enclosed_quotes(char *arg);
char	*escape_sequence(char *arg);

void	exit_status_switch(int status);

char	*ft_strjoin_with_free(char *str1, char *str2);
char	*ft_strtrim_with_free(char *str, char const *set);
char	*ft_strdup_with_free(char *src);

// Free Memory
void	minishell_finalize(void);
void	hash_free(void *ptr);
void	split_free(char **split);
void	command_free(void *command);

#endif