/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:57:34 by bahn              #+#    #+#             */
/*   Updated: 2021/12/16 16:16:37 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_export(void)
{
	char	**update_env;
	int		env_len;
	int		i;
	
	if (g_data.argv[1] == NULL)
		return (SELF_PROC);
	env_len = 0;
	while (g_data.env[env_len] != NULL)
		env_len++;
	update_env = ft_calloc(sizeof(char *), env_len + 2);
	i = -1;
	while (++i < env_len)
	{
		update_env[i] = ft_strdup(g_data.env[i]);
		free(g_data.env[i]); 
	}
	free(g_data.env);
	update_env[i] = ft_strdup(g_data.argv[1]);
	update_env[++i] = NULL;
	g_data.env = update_env;
	return (EXEC_PROC);
}