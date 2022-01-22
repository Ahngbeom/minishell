/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incorrect_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:25:03 by bahn              #+#    #+#             */
/*   Updated: 2022/01/22 13:44:22 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	No Options
*/
int	incorrect_exit(t_command *command)
{
	ft_putendl_fd(command->argv[0], 1);
	if (argv_counter(command->argv) > 1)
		printf("minishell: exit: %s: numeric argument required\n", \
				command->argv[1]);
	ft_lstclear(&g_data.lst_cmds, command_free);
	minishell_finalize();
	exit(ft_atoi(g_data.exit_stat));
}
