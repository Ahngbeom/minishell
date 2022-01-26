/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:48:40 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 22:56:48 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	delete_first(void)
{
	t_list	*temp;

	temp = g_data.lst_env->next;
	ft_lstdelone(g_data.lst_env, hash_free);
	g_data.lst_env = temp;
}

static	void	delete_other(char *key)
{
	t_list	*ptr;
	t_hash	*hash;
	t_list	*temp;

	ptr = g_data.lst_env;
	while (ptr != NULL)
	{
		if (ptr->next != NULL)
			hash = ptr->next->content;
		else
			break ;
		if (!ft_strncmp(hash->key, key, ft_strlen(hash->key) + 1))
		{
			temp = ptr->next->next;
			ft_lstdelone(ptr->next, hash_free);
			ptr->next = temp;
			break ;
		}
		ptr = ptr->next;
	}
}

static	void	delete_envv(char *key)
{
	t_hash	*hash;

	hash = g_data.lst_env->content;
	if (!ft_strncmp(hash->key, key, ft_strlen(hash->key) + 1))
		delete_first();
	else
		delete_other(key);
}

/*
	No Options
*/
int	minishell_unset(t_command *command)
{
	t_pipe	pipe_data;
	int		i;

	set_pipe(&pipe_data);
	if (argv_counter(command->argv) == 1)
		return (release_pipe(&pipe_data));
	i = 0;
	while (command->argv[++i] != NULL)
	{
		if (envv_name_format_checker(command->argv[i]))
		{
			minishell_error(&pipe_data, command->argv[0], command->argv[i], \
								"not a valid identifier");
			continue ;
		}
		delete_envv(command->argv[i]);
	}
	return (release_pipe(&pipe_data));
}
