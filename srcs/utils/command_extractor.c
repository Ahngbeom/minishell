/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_extractor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:27:39 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 20:32:47 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	move_and_split(char **input, char **splitted, int length)
{
	char	*temp;

	*splitted = ft_substr(*input, 0, length);
	temp = *input;
	*input = ft_substr(*input, length, ft_strlen(*input));
	free(temp);
	if (ft_strlen(*splitted) != length)
	{
		temp = *splitted;
		*splitted = ft_substr(*input, 0, length);
		free(temp);
	}
	return (1);
}

size_t	command_extractor(char **input, char **splitted)
{
	char	*ptr;
	int		length;
	int		q_finder;

	ptr = *input;
	length = 0;
	while (*ptr != '\0')
	{
		q_finder = quote_finder(&ptr, &length, input);
		if (q_finder == -1)
			return (q_finder);
		else if (q_finder)
			continue ;
		if (type_finder(ptr, &length, input))
			break ;
		length++;
		ptr++;
	}
	if (length > 0)
		return (move_and_split(input, splitted, length));
	return (0);
}
