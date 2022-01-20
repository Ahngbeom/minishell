/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:25:37 by bahn              #+#    #+#             */
/*   Updated: 2022/01/19 00:57:20 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	No Options
*/
int	minishell_pwd(t_command *command)
{
	t_pipe	pipe_data;
	char	*cwd;

	set_pipe(&pipe_data);
	if (argv_counter(command->argv) > 1)
		printf("minishell: pwd: ignoring non-option arguments\n");
	else if (command->argv[1] && *command->argv[1] == '-')
		printf("minishell: pwd: %s: invalid option\n", command->argv[1]);
	else
	{
		cwd = getcwd(NULL, 0);
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
	}
	return (release_pipe(&pipe_data));
}
