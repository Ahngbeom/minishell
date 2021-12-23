/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 21:58:54 by bahn              #+#    #+#             */
/*   Updated: 2021/12/23 15:49:40 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*homepath_translator(char *path)
{
	char	*result;
	char	*temp;

	if (*path == '~')
	{
		temp = ft_substr(path, 1, ft_strlen(path) - 1);
		result = ft_strjoin(getenv("HOME"), temp);
		free(temp);
		return (result);
	}
	else
		return (path);
}

int	minishell_cd(t_command *command)
{
	char	*parse_path;

	if (argv_counter(command->argv) > 2)
		printf("minishell: cd: too many arguments\n");
	else
	{
		command->argv[1] = remove_enclosed_quotes(command->argv[1]);
		if (command->argv[1] == NULL || !ft_strncmp(command->argv[1], "~", ft_strlen(command->argv[1]) + 1))
		{
			if (chdir(getenv("HOME")) == -1)
				printf("minishell: cd: %s: %s\n", getenv("HOME"), strerror(errno));
		}
		else if (command->argv[1] != NULL)
		{
			parse_path = homepath_translator(command->argv[1]);
			if (parse_path != NULL)
			{
				if (chdir(parse_path) == -1)
					printf("minishell: cd: %s: %s\n", command->argv[1], strerror(errno));
				if (parse_path != command->argv[1])
					free(parse_path);
			}
		}
	}
	return (SELF_PROC);
}
