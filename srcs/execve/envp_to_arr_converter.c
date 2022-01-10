/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_arr_converter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:33:21 by bahn              #+#    #+#             */
/*   Updated: 2022/01/11 01:39:18 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_to_arr_converter(t_list *list)
{
	t_list	*envv;
	t_hash	*hash;
	char	**envp;
	char	*temp;
	int		i;

	envp = ft_calloc(sizeof(char *), ft_lstsize(list));
	envv = list;
	i = -1;
	while (envv != NULL)
	{
		hash = (t_hash *)envv->content;
		temp = ft_strjoin(hash->key, "=");
		envp[++i] = ft_strjoin(temp, hash->value);
		free(temp);
		envv = envv->next;
	}
	return (envp);
}
