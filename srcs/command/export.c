/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:57:34 by bahn              #+#    #+#             */
/*   Updated: 2022/01/14 13:38:07 by bahn             ###   ########.fr       */
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

	ptr = *g_data.envv;
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

	if (argv_counter(argv) != 1)
		return (0);
	ptr = *g_data.envv;
	while (ptr != NULL)
	{
		printf("declare -x %s=\"%s\"\n", ((t_hash *)ptr->content)->key, ((t_hash *)ptr->content)->value);
		ptr = ptr->next;
	}
	return (1);
}

int	minishell_export(t_command *command)
{
	t_list	*ptr;
	t_hash	*hash;
	char	**temp;
	int		i;

	if (noarguments_export(command->argv))
		return (EXIT_SUCCESS);
	i = 0;
	while (command->argv[++i] != NULL)
	{
		if (export_format_checker(command->argv[i]))
			continue ;
		temp = ft_split(command->argv[i], '=');
		if (envv_name_format_checker(temp[0]))
		{
			printf("bash: export: `%s': not a valid identifier\n", command->argv[i]);
			split_free(temp);
			continue ;
		}
		hash = ft_calloc(sizeof(t_hash), 1);
		hash->key = temp[0];
		hash->value = temp[1];
		free(temp);
		ptr = export_dupl_checker(hash->key);
		if (ptr)
		{
			free(hash->key);
			free(((t_hash *)ptr->content)->value);
			((t_hash *)ptr->content)->value = hash->value;
			free(hash);
		}
		else
			ft_lstadd_back(g_data.envv, ft_lstnew(hash));
	}
	return (EXIT_SUCCESS);
}
