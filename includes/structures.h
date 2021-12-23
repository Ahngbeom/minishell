/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:48:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/23 21:55:24 by bahn             ###   ########.fr       */
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
	char		*prompt;
	t_list		**envv;

	char		**arr_redirect;

	t_list		*command;

	int			*pipe;
	char		*output;
};

struct s_hash
{
	char	*key;
	char	*value;
};

struct s_command
{
	int			(*func)(t_command *);
	char		**argv;
	char		*redirect;
};

#endif