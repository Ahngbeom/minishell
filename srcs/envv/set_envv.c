/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:11:14 by bahn              #+#    #+#             */
/*   Updated: 2022/01/17 22:36:42 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*set_lstenvv(char *env[])
{
	t_list	*lst;
	t_hash	*hash;
	char	**temp;
	int		i;

	lst = NULL;
	i = -1;
	while (env[++i] != NULL)
	{
		temp = ft_split(env[i], '=');
		hash = ft_calloc(sizeof(t_hash), 1);
		hash->key = temp[0];
		hash->value = temp[1];
		free(temp);
		if (lst == NULL)
			lst = ft_lstnew(hash);
		else
			ft_lstadd_back(&lst, ft_lstnew(hash));
	}
	return (lst);
}

char	**set_envvpath(void)
{
	int		i;
	char	**envv_path;
	char	*temp;

	if (g_data.envv_path != NULL)
		split_free(g_data.envv_path);
	if (get_envv_value("PATH") == NULL)
		return (NULL);
	envv_path = ft_split(get_envv_value("PATH"), ':');
	i = -1;
	while (envv_path[++i] != NULL)
	{
		if (envv_path[i][ft_strlen(envv_path[i]) - 1] != '/')
		{
			temp = envv_path[i];
			envv_path[i] = ft_strjoin(envv_path[i], "/");
			free(temp);
		}
	}
	return (envv_path);
}
