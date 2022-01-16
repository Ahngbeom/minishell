/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:48:53 by bahn              #+#    #+#             */
/*   Updated: 2022/01/17 01:04:12 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libft.h"

typedef struct termios		t_termios;
typedef struct s_data		t_data;
typedef struct s_hash		t_hash;
typedef struct s_command	t_command;

extern t_data				g_data;

t_data						g_data;

struct s_data
{
	char			*prompt;
	char			**org_envv;
	t_list			**envv;
	char			**envv_path;

	char			**arr_redirect;

	t_list			*commands;
	char			*exit_stat;

	int				*pipe;
	char			*input;
	char			*output;
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

	// char		*output;
	int			o_flag;
	// char		*target;

	int			next_flag;
	int			pre_flag;
	
	// t_list		*list;
};

#endif