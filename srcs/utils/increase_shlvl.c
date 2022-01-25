/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase_shlvl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:25:13 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 21:28:03 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increase_shlvl(void)
{
	t_hash	*envv;
	char	*temp;

	envv = get_envv("SHLVL");
	if (envv == NULL)
		return ;
	temp = envv->value;
	envv->value = ft_itoa(ft_atoi(get_envv("SHLVL")->value) + 1);
	free(temp);
}
