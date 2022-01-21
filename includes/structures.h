/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:48:53 by bahn              #+#    #+#             */
/*   Updated: 2022/01/21 14:06:10 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libft.h"

typedef struct termios		t_termios;
typedef struct s_data		t_data;
typedef struct s_hash		t_hash;
typedef struct s_command	t_command;
typedef struct s_pip		t_pip;
typedef struct s_pipe		t_pipe;

extern t_data				g_data;

t_data						g_data;

struct s_command
{
	// Value is 1 If this Command is Built-in(bash) Command
	// Not is 0 (Zero)
	int			bulit_in_flag;

	int			(*builtin_func)(t_command *);
	// int			(*func)(t_command *);
	char		**argv;
	char		*type;

	t_list		*lst_argv;
	// char		*redirect;

	// 리다이렉션, 파이프를 처리하기위해 출력 결과를 저장하기 위한 변수
	char		*output;

	int			next_flag;
	int			pre_flag;
};

struct s_pip
{
	int		size;
	int		i;
	int		**fd;
	pid_t	pid;
	int		status;
	t_command	*exe;
};

struct s_data
{
	char			*prompt;
	t_list			*lst_env;
	char			**envv_path;

	char			**arr_redirect;

	t_list			*commands;
	char			*exit_stat;
	int				status;

	int				not_convert;
};

struct s_hash
{
	char	*key;
	char	*value;
};

// struct s_command
// {
// 	int			(*builtin_func)(t_command *);
// 	char		**argv;
// 	char		*type;

// 	// int			o_flag;

// 	// int			next_flag;
// 	// int			pre_flag;
// };

struct s_pipe
{
	int		org_stdioe[2];
	int		fd[2];
};

#endif