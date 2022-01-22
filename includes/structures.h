/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:48:53 by bahn              #+#    #+#             */
/*   Updated: 2022/01/22 13:43:37 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libft.h"

typedef struct termios		t_termios;
typedef struct s_data		t_data;
typedef struct s_hash		t_hash;
typedef struct s_command	t_command;
typedef struct s_pipe		t_pipe;

extern t_data				g_data;

t_data						g_data;

struct s_data
{
	char			*prompt;

	t_list			*lst_cmds;
	
	t_list			*lst_env;
	char			**envv_path;

	char			**arr_redirect;

	char			*exit_stat;
};

struct s_hash
{
	char	*key;
	char	*value;
};

struct s_command
{
	int			(*builtin_func)(t_command *);
	char		**argv;
	char		*type;

	// int			o_flag;

	// int			next_flag;
	// int			pre_flag;
};

struct s_pipe
{
	int		org_stdioe[2];
	int		fd[2];
};

#endif