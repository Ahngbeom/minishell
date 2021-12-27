/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_enclosed_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:30:34 by bahn              #+#    #+#             */
/*   Updated: 2021/12/27 11:24:25 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	more_input(char **arg)
{
	char	*more_input;
	char	*result;
	char	*temp;

	temp = *arg;
	result = ft_strjoin(*arg, "\n");
	free(temp);
	more_input = readline("> ");
	temp = result;
	result = ft_strjoin(result, more_input);
	free(temp);
	free(more_input);
	*arg = result;
	return (1);
}

static	int	arg_compose(char **arg, char *open_quotes, char *close_quotes)
{
	char	*origin;
	char	*temp1;
	char	*temp2;
	
	origin = ft_substr(*arg, 0, ft_strlen(*arg) - ft_strlen(open_quotes));
	temp1 = origin;
	temp2 = ft_substr(open_quotes, 1, close_quotes - open_quotes - 1);
	origin = ft_strjoin(origin, temp2);
	free(temp1);
	free(temp2);
	if (*(close_quotes + 1) != '\0')
	{
		*arg = ft_strjoin(origin, close_quotes + 1);
		free(origin);
	}
	else
	{
		free(*arg);
		*arg = origin;
	}
	return (1);
}

static	int	quotes_finder(char **arg, char quetes)
{
	char	*find;
	char	*r_find;

	find = ft_strchr(*arg, quetes);
	if (find != NULL && *(find - sizeof(char)) != '\\')
	{
		r_find = ft_strrchr(*arg, quetes);
		if (find == r_find)
			return (more_input(arg));
		else
			return (arg_compose(arg, find, r_find));
	}
	else
		return (0);
}

char	*remove_enclosed_quotes(char *arg)
{
	char	*result;
	
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
		continue ;
	return (result);
}
