/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:48:53 by bahn              #+#    #+#             */
/*   Updated: 2021/12/28 11:04:55 by bahn             ###   ########.fr       */
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
	char		**org_envv;
	t_list		**envv;
	char		**envv_path;
	
	char		**arr_redirect;

	t_list		*commands;
	int			status;

	int			*pipe;
};

struct s_hash
{
	char	*key;
	char	*value;
};

struct s_command
{
	// Value is 1 If this Command is Built-in(bash) Command 
	// Not is 0 (Zero)
	int			bulit_in_flag;
	
	int			(*func)(t_command *);
	char		**argv;
	char		*redirect;
	
	// 리다이렉션, 파이프를 처리하기위해 출력 결과를 저장하기 위한 변수
	char		*output;
};

#endif