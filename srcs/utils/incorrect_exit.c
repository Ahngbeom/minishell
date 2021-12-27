/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incorrect_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:25:03 by bahn              #+#    #+#             */
/*   Updated: 2021/12/27 12:12:19 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	incorrect_exit(t_command *command)
{
	ft_putendl_fd(command->argv[0], 1);
	if (argv_counter(command->argv) > 1)
		printf("minishell: exit: %s: numeric argument required\n", command->argv[1]);
	ft_lstclear(&g_data.commands, command_free);
	minishell_finalize();
	exit(EXIT_FAILURE);
	return (SELF_PROC);
}