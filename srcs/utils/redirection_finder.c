/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_finder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:06:05 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 10:41:03 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_chekcer(char *input, char **r_addr, char *redirection)
{
	char	*ptr;

	ptr = input;
	*r_addr = ft_strnstr(ptr, redirection, ft_strlen(input));
	while (*r_addr)
	{
		if (ft_strchr(ptr, '\'') != NULL && \
			ft_strchr(ptr, '\'') < *r_addr && \
			ft_strchr(ft_strchr(ptr, '\'') + 1, '\'') > *r_addr)
		{
			ptr = ft_strchr(ft_strchr(ptr, '\'') + 1, '\'') + 1;
			*r_addr = ft_strnstr(ptr, redirection, ft_strlen(input));
		}
		else if (ft_strchr(ptr, '\"') != NULL && \
			ft_strchr(ptr, '\"') < *r_addr && \
			ft_strchr(ft_strchr(ptr, '\"') + 1, '\"') > *r_addr)
		{
			ptr = ft_strchr(ft_strchr(ptr, '\"') + 1, '\"') + 1;
			*r_addr = ft_strnstr(ptr, redirection, ft_strlen(input));
		}
		else
			break ;
	}
}

int	redirection_finder(char *redirection[], char *input, char **save)
{
	char	*find_ptr;
	char	*forefront;
	int		i;

	forefront = NULL;
	find_ptr = NULL;
	i = -1;
	while (redirection[++i] != NULL)
	{
		quotes_chekcer(input, &find_ptr, redirection[i]);
		if (find_ptr != NULL && (forefront == NULL || forefront >= find_ptr))
		{
			forefront = find_ptr;
			if (save != NULL)
				*save = redirection[i];
		}
	}
	if (forefront != NULL)
		return (forefront - input);
	else
		return (-1);
}
