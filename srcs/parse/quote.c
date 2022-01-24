/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 01:12:35 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 20:33:17 by bahn             ###   ########.fr       */
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

void	remove_quotes(t_command *command)
{
	int		i;
	char	*temp;

	i = -1;
	while (command->argv[++i] != NULL)
	{
		if (command->argv[i][0] == '\'')
		{
			temp = command->argv[i];
			command->argv[i] = ft_strtrim(command->argv[i], "\'");
			free(temp);
		}
		else if (command->argv[i][0] == '\"')
		{
			temp = command->argv[i];
			command->argv[i] = ft_strtrim(command->argv[i], "\"");
			free(temp);
			envmark_converter(&command->argv[i]);
		}
		else
			envmark_converter(&command->argv[i]);
	}	
}
