/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:48:40 by bahn              #+#    #+#             */
/*   Updated: 2021/12/23 21:21:21 by bahn             ###   ########.fr       */
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

static	t_list	*key_finder(char *key)
{
	t_list	*ptr;

	ptr = *g_data.envv;
	while (ptr != NULL)
	{
		if (!ft_strncmp(key, ((t_hash *)ptr->content)->key, ft_strlen(key) + 1))
			return (ptr);
		ptr = ptr->next;
	}
	return (ptr);
}

static	void	delete_envv(t_list *env)
{
	t_list	**new_envv;
	t_list	*ptr;
	t_list	*temp;

	new_envv = ft_calloc(sizeof(t_list *), ft_lstsize(*g_data.envv) - 1);
	ptr = *g_data.envv;
	while (ptr != NULL)
	{
		temp = ptr->next;
		if (ptr == env)
		{
			free(((t_hash *)ptr->content)->key);
			free(((t_hash *)ptr->content)->value);
			free(((t_hash *)ptr->content));
			free(ptr);
		}
		else
		{
			ptr->next = NULL;
			ft_lstadd_back(new_envv, ptr);
		}
		ptr = temp;
	}
	g_data.envv = new_envv;
}

int	minishell_unset(t_command *command)
{
	t_list	*del_env;
	int		i;

	if (argv_counter(command->argv) == 1)
		return (SELF_PROC);
	i = 0;
	while (command->argv[++i] != NULL)
	{
		if (envv_name_format_checker(command->argv[i]))
			printf("bash: unset: `%s': not a valid identifier\n", command->argv[i]);
		command->argv[i] = remove_envmark(command->argv[i]);
		del_env = key_finder(command->argv[i]);
		if (del_env != NULL)
			delete_envv(del_env);
	}
	return (SELF_PROC);
}