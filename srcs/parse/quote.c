/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 01:12:35 by bahn              #+#    #+#             */
/*   Updated: 2022/01/23 04:29:06 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	move_to_end_quotes(char **ptr, int *length, char quotes)
{
	char	*endq;

	endq = ft_strrchr(*ptr, quotes);
	if (endq != NULL)
	{
		*length = (++endq) - *ptr;
		*ptr = endq;
	}
	else
		more_input2(*ptr, quotes);
	return (1);
}

int	quote_finder(char **ptr, int *length)
{
	char	*sgle;
	char	*dble;

	sgle = ft_strchr(*ptr, '\'');
	dble = ft_strchr(*ptr, '\"');
	if (sgle && dble)
	{
		if (sgle < dble)
			return (move_to_end_quotes(ptr, length, '\''));
		else
			return (move_to_end_quotes(ptr, length, '\"'));
	}
	else if (sgle)
		return (move_to_end_quotes(ptr, length, '\''));
	else if (dble)
		return (move_to_end_quotes(ptr, length, '\"'));
	return (0);
}

void	remove_quotes(char **str)
{
	char	*sgle;
	char	*dble;
	char	*endq;
	char	*temp;

	temp = NULL;
	sgle = ft_strchr(*str, '\'');
	dble = ft_strchr(*str, '\"');
	if (sgle && dble)
	{
		if (sgle < dble)
		{
			temp = ft_substr(*str, 0, sgle - *str);
			sgle = ft_substr(sgle, 1, ft_strchr(sgle, '\'') - (sgle + 1));
			endq = *str;
			*str = ft_strjoin_with_free(temp, sgle);
			free(endq);
		}
		else
		{
			temp = ft_substr(*str, 0, sgle - *str);
			sgle = ft_substr(sgle, 1, ft_strchr(sgle, '\"') - (sgle + 1));
			endq = *str;
			*str = ft_strjoin_with_free(temp, sgle);
			free(endq);
		}
	}
	else if (sgle)
	{
		temp = ft_substr(*str, 0, sgle - *str);
		sgle = ft_substr(sgle, 1, ft_strchr(sgle, '\'') - (sgle + 1));
		endq = *str;
		*str = ft_strjoin_with_free(temp, sgle);
		free(endq);
	}
	else if (dble)
	{
		temp = ft_substr(*str, 0, sgle - *str);
		sgle = ft_substr(sgle, 1, ft_strchr(sgle, '\"') - (sgle + 1));
		endq = *str;
		*str = ft_strjoin_with_free(temp, sgle);
		free(endq);
	}
	else
		return ;
}
