/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 02:02:00 by bahn              #+#    #+#             */
/*   Updated: 2022/01/18 02:05:22 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_envv(char *key, char *new_value)
{
	char	*temp;

	temp = get_envv(key)->value;
	get_envv(key)->value = ft_strdup(new_value);
	free(temp);
}
