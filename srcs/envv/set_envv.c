/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:11:14 by bahn              #+#    #+#             */
/*   Updated: 2022/01/18 21:24:30 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_hash(char **split, t_hash **hash)
{
	int		i;

	(*hash)->key = split[0];
	if (split[1] == NULL)
		(*hash)->value = ft_strdup("");
	i = 0;
	while (split[++i] != NULL)
	{
		if ((*hash)->value == NULL)
			(*hash)->value = split[i];
		else
			(*hash)->value = ft_strjoin_with_free((*hash)->value, split[i]);
	}
	free(split);
}

t_list	*set_lstenvv(char *env[])
{
	t_list	*lst;
	t_hash	*hash;
	char	**split;
	int		i;

	lst = NULL;
	i = -1;
	while (env[++i] != NULL)
	{
		split = ft_split(env[i], '=');
		hash = ft_calloc(sizeof(t_hash), 1);
		set_hash(split, &hash);
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
