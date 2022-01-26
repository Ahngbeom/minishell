/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 01:12:35 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 20:14:34 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	move_to_end_quotes(char **ptr, int *length, char quotes, \
								char **input)
{
	char	*endq;

	endq = ft_strchr((*ptr) + 1, quotes);
	if (endq != NULL)
	{
		++endq;
		*length = endq - *input;
		*ptr = endq;
	}
	else
	{
		printf("minishell: `%c': Not enclosed quotes\n", quotes);
		exit_status_switch(2);
		return (-1);
	}
	return (1);
}

int	quote_finder(char **ptr, int *length, char **input)
{
	if (**ptr == '\'')
		return (move_to_end_quotes(ptr, length, '\'', input));
	else if (**ptr == '\"')
		return (move_to_end_quotes(ptr, length, '\"', input));
	else
		return (0);
}
