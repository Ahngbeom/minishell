/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 22:35:37 by bahn              #+#    #+#             */
/*   Updated: 2022/01/17 22:35:54 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hash	*get_envv(char *key)
{
	t_list	*ptr;

	ptr = g_data.lst_env;
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

	ptr = g_data.lst_env;
	while (ptr != NULL)
	{
		if (!ft_strncmp(((t_hash *)ptr->content)->key, key, ft_strlen(key) + 1))
			return (((t_hash *)ptr->content)->value);
		ptr = ptr->next;
	}
	return (NULL);
}
