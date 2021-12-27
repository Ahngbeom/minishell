/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:25:37 by bahn              #+#    #+#             */
/*   Updated: 2021/12/27 12:19:51 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_pwd(t_command *command)
{
	if (argv_counter(command->argv) > 1)
		printf("minishell: pwd: ignoring non-option arguments\n");
	else if (*command->argv[1] == '-')
		printf("minishell: pwd: %s: invalid option\n", command->argv[1]);
	else
		ft_putendl_fd(getcwd(NULL, 0), 1);
	return (SELF_PROC);
}