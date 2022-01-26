/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_switch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:49:15 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 15:34:28 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_switch(int status)
{
	char	*temp;

	temp = g_data.exit_stat;
	g_data.exit_stat = ft_itoa(status);
	free(temp);
}
