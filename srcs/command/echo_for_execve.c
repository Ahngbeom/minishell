/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_for_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:46:46 by bahn              #+#    #+#             */
/*   Updated: 2021/12/27 17:42:39 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	n_flag_checker(char *argv)
{
	int		j;
	
	if (argv[0] == '-')
	{
		j = 1;
		while (argv[j] == 'n' && argv[j] != '\0')
			j++;
		if (argv[j] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

// static	char	*remove_backslash(char *arg)
// {
// 	char	*result;
// 	char	*ptr;
// 	char	*find;
// 	char	*temp;

// 	result = ft_strdup(arg);
// 	ptr = arg;
// 	while (*ptr != '\0' && (find = ft_strchr(ptr, '\\')))
// 	{
// 		if (*(find + 1) == '\\')
// 			find++;
// 		temp = ft_substr(ptr, 0, ft_strlen(ptr) - ft_strlen(find));
// 		free(result);
// 		result = ft_strjoin(temp, find + 1);
// 		free(temp);
// 		ptr = find + 1;
// 	}
// 	return (result);
// }

static	char	*envv_converter(char *env)
{
	char	*result;
	char	*temp;

	if (*env == '$')
	{
		// Try echo $HOME\\\\ on bash and minishell
		// Try echo $HOME\\\ on bash and minishell
		if (!envv_name_format_checker(env + sizeof(char)))
		{
			if (envv_getvalue((env + sizeof(char))))
				result = ft_strdup(envv_getvalue((env + sizeof(char))));
			else
				result = ft_strdup("");
		}
		else
		{
			temp = ft_substr(env, 1, envv_name_format_checker(env + sizeof(char)) - env - 1);
			result = ft_strjoin(envv_getvalue(temp), envv_name_format_checker(env + sizeof(char)));
			free(temp);
		}
		free(env);
		return (result);
	}
	return (env);
}

int	minishell_echo_for_execve(t_command *command)
{
	int		i;

	i = 0;
	while (command->argv[++i] != NULL)
	{
		if (i == 1 && n_flag_checker(command->argv[i]))
			continue ;
		command->argv[i] = remove_enclosed_quotes(command->argv[i]);
		if (i > 0)
		{
			// command->argv[i] = remove_backslash(command->argv[i]);
			printf("%s\n", command->argv[i]);
			command->argv[i] = escape_sequence(command->argv[i]);
			command->argv[i] = envv_converter(command->argv[i]);
		}
	}
	return (SELF_PROC);
}
