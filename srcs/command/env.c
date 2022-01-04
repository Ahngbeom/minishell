/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:08:21 by bahn              #+#    #+#             */
/*   Updated: 2022/01/04 14:30:41 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_env(t_command *command)
{
	t_list	*ptr;

	command->bulit_in_flag = 1;
	ptr = *g_data.envv;
	while (ptr != NULL)
	{
		ft_putstr_fd(((t_hash *)ptr->content)->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(((t_hash *)ptr->content)->value, 1);
		ptr = ptr->next;
	}
	return (SELF_PROC);
}
