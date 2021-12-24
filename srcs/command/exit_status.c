/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:21:07 by bahn              #+#    #+#             */
/*   Updated: 2021/12/24 12:39:59 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// $?
int	minishell_exit_status(t_command *command)
{
	(void)command;
	// ft_putnbr_fd(errno, 1);
	ft_putnbr_fd(g_data.status, 1);
	ft_putchar_fd(LF, 1);
	return (SELF_PROC);
}