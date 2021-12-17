/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:57:34 by bahn              #+#    #+#             */
/*   Updated: 2021/12/17 17:50:10 by bahn             ###   ########.fr       */
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

static int	export_dupl_checker(char *arg)
{
	char	**split_temp;
	char	*key;
	char	*temp;
	int	i;

	i = -1;
	split_temp = ft_split(arg, '=');
	key = ft_strdup(split_temp[0]);
	free(split_temp[0]);
	free(split_temp[1]);
	free(split_temp);
	while (g_data.env[++i] != NULL)
	{
		split_temp = ft_split(g_data.env[i], '=');
		if (!ft_strncmp(key, split_temp[0], ft_strlen(key) + 1))
		{
			free(split_temp[0]);
			free(split_temp[1]);
			free(split_temp);
			temp = g_data.env[i];
			g_data.env[i] = ft_strdup(arg);
			free(temp);
			return (1);
		}
	}
	return (0);
}

int	minishell_export(void)
{
	char	**update_env;
	int		env_len;
	int		i;
	
	// 인자가 여려 개일 경우 정상 처리
	
	if (g_data.argv[1] == NULL)
		return (SELF_PROC);
	if (export_format_checker(g_data.argv[1]))
		return (SELF_PROC);
	if (export_dupl_checker(g_data.argv[1]))
		return (SELF_PROC);
	env_len = 0;
	while (g_data.env[env_len] != NULL)
		env_len++;
	update_env = ft_calloc(sizeof(char *), env_len + 2);
	i = -1;
	while (++i < env_len)
	{
		update_env[i] = g_data.env[i];
	}
	free(g_data.env);
	update_env[i] = ft_strdup(g_data.argv[1]);
	update_env[++i] = NULL;
	g_data.env = update_env;
	return (EXEC_PROC);
}

// For t_list
int	minishell_export2(void)
{
	t_hash	*hash;
	char	**temp;
	int		i;

	// 인자가 여려 개일 경우 정상 처리해야함 !
	
	if (g_data.argv[1] == NULL)
		return (SELF_PROC);
	if (export_format_checker(g_data.argv[1]))
		return (SELF_PROC);
	// t_list를 위한 중복체크 필요
	// if (export_dupl_checker(g_data.argv[1]))
		// return (SELF_PROC);
	i = 0;
	while (g_data.argv[++i] != NULL)
	{
		temp = ft_split(g_data.argv[i], '=');
		hash = ft_calloc(sizeof(t_hash), 1);
		hash->key = temp[0];
		hash->value = temp[1];
		free(temp);
		ft_lstadd_back(g_data.envv, ft_lstnew(hash));
	}
	return (SELF_PROC);
}