/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:48:53 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 19:54:21 by minsikim         ###   ########.fr       */
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
	int			bulit_in_flag;

	int			(*builtin_func)(t_command *);
	char		**argv;
	char		*type;

	t_list		*lst_argv;

	char		*output;

	int			next_flag;
	int			pre_flag;
};

struct s_pip
{
	int			size;
	int			i;
	int			**fd;
	pid_t		pid;
	int			status;
	t_command	*exe;
};

struct s_data
{
	char			*prompt;
	t_list			*lst_cmds;
	t_list			*lst_env;
	char			**envv_path;
	char			**arr_redirect;
	char			*exit_stat;
	int				status;

	int				not_convert;
	char			*temp;
	char			**arv;
};

struct s_hash
{
	char	*key;
	char	*value;
};

struct s_pipe
{
	int		org_stdioe[2];
	int		fd[2];
};

#endif