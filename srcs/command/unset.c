/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:48:40 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 00:46:58 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*remove_envmark(char *env)
{
	char	*result;

	if (*env == '$')
	{
		result = ft_substr(env, 1, ft_strlen(env) - 1);
		free(env);
		return (result);
	}
	return (env);
}

t_list	*key_finder(char *key)
{
	t_list	*ptr;

	ptr = g_data.lst_env;
	while (ptr != NULL)
	{
		if (!ft_strncmp(key, ((t_hash *)ptr->content)->key, ft_strlen(key) + 1))
			return (ptr);
		ptr = ptr->next;
	}
	return (ptr);
}

static	void	delete_envv(char *key)
{
	t_list	*ptr;
	t_hash	*hash;
	t_list	*temp;

	hash = g_data.lst_env->content;
	if (!ft_strncmp(hash->key, key, ft_strlen(hash->key) + 1))
	{
		temp = g_data.lst_env->next;
		ft_lstdelone(g_data.lst_env, hash_free);
		g_data.lst_env = temp;
		return ;
	}
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
			printf("minishell: unset: `%s': not a valid identifier\n", \
					command->argv[i]);
			continue ;
		}
		command->argv[i] = remove_envmark(command->argv[i]);
		delete_envv(command->argv[i]);
	}
	return (release_pipe(&pipe_data));
}
