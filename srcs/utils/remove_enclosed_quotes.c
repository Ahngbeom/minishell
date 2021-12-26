/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_enclosed_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:30:34 by bahn              #+#    #+#             */
/*   Updated: 2021/12/26 23:44:42 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	quotes_finder(char **arg, char quetes)
{
	char	*origin;
	char	*find;
	char	*r_find;
	char	*temp;
	char	*temp2;

	find = ft_strchr(*arg, quetes);
	if (find != NULL && *(find - sizeof(char)) != '\\')
	{
		r_find = ft_strrchr(*arg, quetes);
		if (find == r_find)
		{
			return (1);
		}
		else
		{
			origin = ft_substr(*arg, 0, ft_strlen(*arg) - ft_strlen(find) );
			temp = origin;
			temp2 = ft_substr(find, 1, r_find - find - 1);
			origin = ft_strjoin(origin, temp2);
			free(temp);
			free(temp2);
			if (*(r_find + 1) != '\0')
			{
				*arg = ft_strjoin(origin, r_find + 1);
				free(origin);
			}
			else
			{
				free(*arg);
				*arg = origin;
			}
			return (0);
		}
	}
	else
		return (0);
}

char	*remove_enclosed_quotes(char *arg)
{
	char	*more_input;
	char	*result;
	char	*temp;
	
	if (arg == NULL)
		return (arg);
	
	result = arg;
	while ((*arg == '\"' && arg[ft_strlen(arg) - 1] == '\"') \
		||(*arg == '\'' && arg[ft_strlen(arg) - 1] == '\''))
	{
		result = ft_substr(arg, 1, ft_strlen(arg) - 2);
		free(arg);
	}
	while (quotes_finder(&result, '\"') || quotes_finder(&result, '\''))
	{
		temp = result;
		result = ft_strjoin(result, "\n");
		free(temp);
		
		more_input = readline("> ");
		
		temp = result;
		result = ft_strjoin(result, more_input);
		free(temp);
		
		free(more_input);
	}
	return (result);
}
