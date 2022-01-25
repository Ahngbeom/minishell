/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:25:37 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 18:00:05 by minsikim         ###   ########.fr       */
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
	if (command->argv[1] && *command->argv[1] == '-')
		printf("minishell: pwd: %s: invalid option\n", command->argv[1]);
	else
	{
		cwd = getcwd(NULL, 0);
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
	}
	return (release_pipe(&pipe_data));
}
