/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_arr_converter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:33:21 by bahn              #+#    #+#             */
/*   Updated: 2022/01/18 21:16:21 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_to_arr_converter(t_list *list)
{
	t_list	*lst_env;
	t_hash	*hash;
	char	**arr_env;
	int		i;

	arr_env = ft_calloc(sizeof(char *), ft_lstsize(list) + 1);
	lst_env = list;
	i = -1;
	while (lst_env != NULL)
	{
		hash = (t_hash *)lst_env->content;
		arr_env[++i] = \
			ft_strjoin_with_free(ft_strjoin(hash->key, "="), hash->value);
		lst_env = lst_env->next;
	}
	return (arr_env);
}
