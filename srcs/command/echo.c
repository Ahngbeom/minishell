/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:46:46 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 22:57:04 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	n_flag_checker(char *arg)
{
	if (!ft_strncmp(arg, "-n", ft_strlen(arg) + 1))
		return (1);
	else
		return (0);
}

/*
	Allowed Option : -n
*/
int	minishell_echo(t_command *command)
{
	t_pipe	pipe_data;
	int		i;

	set_pipe(&pipe_data);
	i = 0;
	while (command->argv[++i] != NULL)
	{
		if (i == 1 && n_flag_checker(command->argv[i]))
			continue ;
		ft_putstr_fd(command->argv[i], 1);
		if (command->argv[i + 1] != NULL && ft_strlen(command->argv[i]) != 0)
			ft_putchar_fd(' ', 1);
	}
	if (command->argv[1] == NULL || !(n_flag_checker(command->argv[1])))
		ft_putchar_fd('\n', 1);
	return (release_pipe(&pipe_data));
}
