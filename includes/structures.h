/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:48:53 by bahn              #+#    #+#             */
/*   Updated: 2022/01/14 15:05:28 by bahn             ###   ########.fr       */
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

	char		*output;

	int			next_flag;
	int			pre_flag;
};

#endif