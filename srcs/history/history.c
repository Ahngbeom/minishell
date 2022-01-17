/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:37:28 by bahn              #+#    #+#             */
/*   Updated: 2022/01/18 01:42:27 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_history(t_list *lst_env)
{
	t_hash	*hash;

	hash = ft_calloc(sizeof(t_hash), 1);
	hash->key = ft_strdup("HISTFILE");
	hash->value = ft_strjoin(getcwd(NULL, 0), "/.minishell_history");
	ft_lstadd_back(&lst_env, ft_lstnew(hash));
}
