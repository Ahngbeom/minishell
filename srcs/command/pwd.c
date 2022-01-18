/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:25:37 by bahn              #+#    #+#             */
/*   Updated: 2022/01/18 19:56:10 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	No Options
*/
int	minishell_pwd(t_command *command)
{
	t_pipe	pipe_data;

	set_pipe(&pipe_data);
	if (argv_counter(command->argv) > 1)
		printf("minishell: pwd: ignoring non-option arguments\n");
	else if (command->argv[1] && *command->argv[1] == '-')
		printf("minishell: pwd: %s: invalid option\n", command->argv[1]);
	else
		ft_putendl_fd(getcwd(NULL, 0), STDOUT_FILENO);
	return (release_pipe(&pipe_data));
}
