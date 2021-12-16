/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:57:34 by bahn              #+#    #+#             */
/*   Updated: 2021/12/16 22:28:06 by bahn             ###   ########.fr       */
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
		// update_env[i] = ft_strdup(g_data.env[i]);
		// free(g_data.env[i]);
		
		
		update_env[i] = g_data.env[i];

	}
	free(g_data.env);
	update_env[i] = ft_strdup(g_data.argv[1]);
	update_env[++i] = NULL;
	g_data.env = update_env;
	return (EXEC_PROC);
}