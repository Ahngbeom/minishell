/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command_to_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:54:33 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 20:23:37 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_command_to_list(t_list **list, t_command **command)
{
	*command = ft_calloc(sizeof(t_command), 1);
	if (*list == NULL)
		*list = ft_lstnew(*command);
	else
		ft_lstadd_back(list, ft_lstnew(*command));
}
