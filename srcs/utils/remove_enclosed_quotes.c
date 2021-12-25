/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_enclosed_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:30:34 by bahn              #+#    #+#             */
/*   Updated: 2021/12/24 23:14:15 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	quotes_finder(char *argv, char quetes)
{
	char	*find;

	find = ft_strchr(argv, quetes);
	if (find != NULL && *(find - sizeof(char)) != '\\')
	{
		if (find == ft_strrchr(argv, quetes))
		{
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}

char	*remove_enclosed_quotes(char *argv)
{
	char	*more_input;
	char	*result;
	char	*temp;

	if (argv == NULL)
		return (argv);
	result = argv;
	while (quotes_finder(result, '\"') || quotes_finder(result, '\''))
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
	temp = result;
	result = ft_strtrim(result, "\"\'");
	free(temp);
	return (result);
}
