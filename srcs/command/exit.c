/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:25:03 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 21:12:33 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	No Options
*/
int	minishell_exit(t_command *command)
{
	char	*temp;

	ft_putendl_fd(command->argv[0], 1);
	if (argv_counter(command->argv) > 1)
	{
		printf("minishell: exit: %s: numeric argument required\n", \
				command->argv[1]);
		temp = g_data.exit_stat;
		g_data.exit_stat = ft_itoa(2);
		free(temp);
	}
	ft_lstclear(&g_data.lst_cmds, command_free);
	minishell_finalize();
	exit(ft_atoi(g_data.exit_stat));
}

int	exit_checker(char *input)
{
	if (input == NULL || !ft_strncmp(input, "exit", ft_strlen("exit") + 1))
	{
		ft_putendl_fd("exit", 1);
		if (input != NULL)
			free(input);
		return (1);
	}
	return (0);
}
