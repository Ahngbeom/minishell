/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 21:58:54 by bahn              #+#    #+#             */
/*   Updated: 2022/01/18 19:53:09 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	char	*homepath_translator(char *path)
// {
// 	char	*result;
// 	char	*temp;

// 	if (*path == '~')
// 	{
// 		temp = ft_substr(path, 1, ft_strlen(path) - 1);
// 		result = ft_strjoin(getenv("HOME"), temp);
// 		free(temp);
// 		return (result);
// 	}
// 	else
// 		return (path);
// }

/*
	Only Absolute or Relative PATH
*/
int	minishell_cd(t_command *command)
{
	t_pipe	pipe_data;

	set_pipe(&pipe_data);
	if (argv_counter(command->argv) > 2)
		printf("minishell: cd: too many arguments\n");
	else
	{
		update_envv("OLDPWD", get_envv_value("PWD"));
		if (command->argv[1] == NULL)
		{
			if (chdir(getenv("HOME")) == -1)
				printf("minishell: cd: %s: %s\n", \
					command->argv[1], strerror(errno));
		}
		else
		{
			if (chdir(command->argv[1]) == -1)
				printf("minishell: cd: %s: %s\n", \
					command->argv[1], strerror(errno));
		}	
		update_envv("PWD", getcwd(NULL, 0));
	}
	return (release_pipe(&pipe_data));
}
