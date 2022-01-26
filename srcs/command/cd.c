/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 21:58:54 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 17:52:34 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_argu_check(t_command *command, t_pipe *pipe_data)
{
	if (argv_counter(command->argv) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", \
						pipe_data->org_stdioe[STDOUT_FILENO]);
		return (1);
	}
	return (0);
}

static void	chdir_error(t_command *command, t_pipe *pipe_data)
{
	ft_putstr_fd("minishell: cd: ", pipe_data->org_stdioe[STDOUT_FILENO]);
	ft_putstr_fd(command->argv[1], pipe_data->org_stdioe[STDOUT_FILENO]);
	ft_putstr_fd(": ", pipe_data->org_stdioe[STDOUT_FILENO]);
	ft_putendl_fd(strerror(errno), pipe_data->org_stdioe[STDOUT_FILENO]);
}

/*
	Only Absolute or Relative PATH
*/
int	minishell_cd(t_command *command)
{
	t_pipe	pipe_data;
	char	*cwd;

	set_pipe(&pipe_data);
	if (cd_argu_check(command, &pipe_data))
		return (release_pipe(&pipe_data));
	else
	{
		update_envv("OLDPWD", get_envv_value("PWD"));
		if (argv_counter(command->argv) == 1)
		{
			if (chdir(getenv("HOME")) == -1)
				chdir_error(command, &pipe_data);
		}
		else
		{
			if (chdir(command->argv[1]) == -1)
				chdir_error(command, &pipe_data);
		}
		cwd = getcwd(NULL, 0);
		update_envv("PWD", cwd);
		free(cwd);
	}
	return (release_pipe(&pipe_data));
}
