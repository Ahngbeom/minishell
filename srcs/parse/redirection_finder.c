/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_finder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:06:05 by bahn              #+#    #+#             */
/*   Updated: 2022/01/02 22:40:55 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	redirection_finder(char *input, char *redirection[], char **save)
{
	char	*find_ptr;
	char	*forefront;
	int		i;

	forefront = NULL;
	find_ptr = NULL;
	i = -1;
	while (redirection[++i] != NULL)
	{
		find_ptr = ft_strnstr(input, redirection[i], ft_strlen(input));
		if (find_ptr != NULL && (forefront == NULL || forefront > find_ptr))
		{
			forefront = find_ptr;
			if (save != NULL)
				*save = redirection[i];
		}
	}
	if (input < forefront)
		return (forefront - input);
	else
		return (0);
}
