/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 01:12:35 by bahn              #+#    #+#             */
/*   Updated: 2022/01/23 23:24:00 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	move_to_end_quotes(char **ptr, int *length, char quotes, char **input)
{
	char	*endq;

	endq = ft_strchr((*ptr) + 1, quotes);
	// printf("move [%s(%p)] -> [%s(%p)]\n", *ptr, *ptr, endq, endq);
	if (endq != NULL)
	{
		++endq;
		*length = endq - *input;
		*ptr = endq;
	}
	else
		more_input2(*ptr, quotes);
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
		}
	}	
}

// void	remove_quotes(char **str)
// {
// 	char	*sgle;
// 	char	*dble;
// 	char	*endq;
// 	char	*temp;

// 	temp = NULL;
// 	sgle = ft_strchr(*str, '\'');
// 	dble = ft_strchr(*str, '\"');
// 	if (sgle && dble)
// 	{
// 		if (sgle < dble)
// 		{
// 			temp = ft_substr(*str, 0, sgle - *str);
// 			sgle = ft_substr(sgle, 1, ft_strchr(sgle, '\'') - (sgle + 1));
// 			endq = *str;
// 			*str = ft_strjoin_with_free(temp, sgle);
// 			free(endq);
// 		}
// 		else
// 		{
// 			temp = ft_substr(*str, 0, sgle - *str);
// 			sgle = ft_substr(sgle, 1, ft_strchr(sgle, '\"') - (sgle + 1));
// 			endq = *str;
// 			*str = ft_strjoin_with_free(temp, sgle);
// 			free(endq);
// 		}
// 	}
// 	else if (sgle)
// 	{
// 		temp = ft_substr(*str, 0, sgle - *str);
// 		sgle = ft_substr(sgle, 1, ft_strchr(sgle, '\'') - (sgle + 1));
// 		endq = *str;
// 		*str = ft_strjoin_with_free(temp, sgle);
// 		free(endq);
// 	}
// 	else if (dble)
// 	{
// 		temp = ft_substr(*str, 0, sgle - *str);
// 		sgle = ft_substr(sgle, 1, ft_strchr(sgle, '\"') - (sgle + 1));
// 		endq = *str;
// 		*str = ft_strjoin_with_free(temp, sgle);
// 		free(endq);
// 	}
// 	else
// 		return ;
// }
