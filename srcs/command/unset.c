/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:48:40 by bahn              #+#    #+#             */
/*   Updated: 2021/12/16 22:47:59 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_unset(void)
{
	char	*temp;
	int		i;
	int		j;

	if (argv_counter(g_data.argv) <= 1)
		return (SELF_PROC);
	i = 0;
	while (g_data.argv[++i] != NULL)
	{
		if (*g_data.argv[i] == '$')
		{
			temp = g_data.argv[i];
			g_data.argv[i] = ft_substr(g_data.argv[i], 1, ft_strlen(g_data.argv[i]) - 1);
			free(temp);
		}
		j = -1;
		while (g_data.env[++j] != NULL)
		{
			if (!ft_strncmp(g_data.argv[i], g_data.env[j], ft_strlen(g_data.argv[i]) + 1))
			{
				
			}
		}
	}
	
	return (EXEC_PROC);
}