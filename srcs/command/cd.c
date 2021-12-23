/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 21:58:54 by bahn              #+#    #+#             */
/*   Updated: 2021/12/23 14:37:33 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*homepath_translator(char *path)
{
	char	*result;
	char	*temp;
	char	*temp2;

	if (path == NULL)
		return (NULL);
	if (*path == '~')
	{
		result = ft_strjoin(getenv("HOME"), "/");
		temp = ft_substr(path, 1, ft_strlen(path) - 1);
		temp2 = result;
		result = ft_strjoin(result, temp);
		free(temp2);
		free(temp);
		return (result);
	}
	else
		return (path);
}

int	minishell_cd(t_command *command)
{
	char	*temp;

	if (argv_counter(command->argv) > 2)
		printf("minishell: cd: too many arguments\n");
	else
	{
		if (command->argv[1] != NULL)
		{
			temp = command->argv[1];
			command->argv[1] = ft_strtrim(command->argv[1], "\'\"");
			free(temp);
			// command->argv[1] = remove_enclosed_quotes(command->argv[1]);
		}
		if (command->argv[1] == NULL || !ft_strncmp(command->argv[1], "~", ft_strlen(command->argv[1])))
		{
			if (chdir(getenv("HOME")) == -1)
				printf("minishell: cd: %s: %s\n", getenv("HOME"), strerror(errno));
		}
		else if (command->argv[1] != NULL)
		{
			temp = homepath_translator(command->argv[1]);
			if (temp != NULL)
			{
				if (chdir(temp) == -1)
					printf("minishell: cd: %s: %s\n", command->argv[1], strerror(errno));
				if (temp != command->argv[1])
					free(temp);
			}
		}
	}
	return (SELF_PROC);
}
