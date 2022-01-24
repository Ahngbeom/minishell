/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:57:34 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 23:17:54 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_format_checker(char *arg)
{
	char	*ptr;

	ptr = ft_strchr(arg, '=');
	if (ptr != NULL)
	{
		if (ptr == arg || ptr == (arg + ft_strlen(arg) - 1))
			return (1);
		else
			return (0);
	}
	else
		return (1);
}

static t_list	*export_dupl_checker(char *key)
{
	t_list	*ptr;

	ptr = g_data.lst_env;
	while (ptr != NULL)
	{
		if (!ft_strncmp(((t_hash *)ptr->content)->key, key, ft_strlen(key) + 1))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

static int	noarguments_export(char	*argv[])
{
	t_list	*ptr;
	t_hash	*hash;

	if (argv_counter(argv) != 1)
		return (0);
	ptr = g_data.lst_env;
	while (ptr != NULL)
	{
		hash = ptr->content;
		printf("declare -x %s=\"%s\"\n", hash->key, hash->value);
		ptr = ptr->next;
	}
	return (1);
}

static void	envv_register(char **key_value)
{
	t_hash	*hash;
	t_list	*exist;

	hash = ft_calloc(sizeof(t_hash), 1);
	hash->key = key_value[0];
	hash->value = key_value[1];
	free(key_value);
	exist = export_dupl_checker(hash->key);
	if (exist)
	{
		free(((t_hash *)exist->content)->value);
		((t_hash *)exist->content)->value = ft_strdup(hash->value);
		hash_free(hash);
	}
	else
		ft_lstadd_back(&g_data.lst_env, ft_lstnew(hash));
}

/*
	No Options
*/
int	minishell_export(t_command *command)
{
	t_pipe	pipe_data;
	char	**split;
	int		i;

	set_pipe(&pipe_data);
	if (noarguments_export(command->argv))
		return (release_pipe(&pipe_data));
	i = 0;
	while (command->argv[++i] != NULL)
	{
		if (export_format_checker(command->argv[i]))
			continue ;
		split = ft_split(command->argv[i], '=');
		if (envv_name_format_checker(split[0]))
		{
			minishell_error(&pipe_data, command->argv[0], command->argv[i], \
							"not a valid identifier");
			split_free(split);
			continue ;
		}
		envv_register(split);
	}
	return (release_pipe(&pipe_data));
}
