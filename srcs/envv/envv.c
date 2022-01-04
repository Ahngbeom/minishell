/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:11:14 by bahn              #+#    #+#             */
/*   Updated: 2022/01/04 14:16:18 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_envvpath(void)
{
	int		i;
	char	*temp;

	g_data.envv_path = ft_split(getenv("PATH"), ':');
	i = -1;
	while (g_data.envv_path[++i] != NULL)
	{
		if (g_data.envv_path[i][ft_strlen(g_data.envv_path[i]) - 1] != '/')
		{
			temp = g_data.envv_path[i];
			g_data.envv_path[i] = ft_strjoin(g_data.envv_path[i], "/");
			free(temp);
		}
	}
}

t_hash	*get_envv(char *key)
{
	t_list	*ptr;

	ptr = *g_data.envv;
	while (ptr != NULL)
	{
		if (!ft_strncmp(((t_hash *)ptr->content)->key, key, ft_strlen(key) + 1))
			return ((t_hash *)ptr->content);
		ptr = ptr->next;
	}
	return (NULL);
}

char	*get_envv_value(char *key)
{
	t_list	*ptr;

	ptr = *g_data.envv;
	while (ptr != NULL)
	{
		if (!ft_strncmp(((t_hash *)ptr->content)->key, key, ft_strlen(key) + 1))
			return (((t_hash *)ptr->content)->value);
		ptr = ptr->next;
	}
	return (NULL);
}

char	*envv_name_format_checker(char *key)
{
	int	i;

	i = -1;
	while (key[++i] != '\0')
	{
		if (ft_isalpha(key[i]) == 0 && key[i] != '_')
			break ;
	}
	if (key[i] != '\0')
		return (&key[i]);
	else
		return (NULL);
}

t_list	**set_lstenvv(char *env[])
{
	t_list	**lst;
	t_hash	*hash;
	char	**temp;
	int		env_len;
	int		i;

	i = -1;
	env_len = 0;
	while (env[++i] != NULL)
		env_len++;
	lst = ft_calloc(sizeof(t_list *), env_len);
	i = -1;
	while (env[++i] != NULL)
	{
		temp = ft_split(env[i], '=');
		hash = ft_calloc(sizeof(t_hash), 1);
		hash->key = temp[0];
		hash->value = temp[1];
		free(temp);
		ft_lstadd_back(lst, ft_lstnew(hash));
	}
	return (lst);
}
