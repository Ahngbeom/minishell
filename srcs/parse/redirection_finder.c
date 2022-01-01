/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_finder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:06:05 by bahn              #+#    #+#             */
/*   Updated: 2022/01/02 00:47:02 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*redirection_finder(char **input, char *redirection)
{
	char	*find_ptr;
	char	*forefront;
	int		i;

	forefront = NULL;
	find_ptr = NULL;
	i = -1;
	while (redirection[++i] != NULL)
	{
		find_ptr = ft_strnstr(*input, redirection[i], ft_strlen(*input));
		printf("find_ptr : %s\n", find_ptr);
		if (find_ptr != NULL && (forefront == NULL || forefront > find_ptr))
			forefront = find_ptr;
	}
	if (forefront != NULL)
		*input = forefront + 1;
	return (forefront);
}


char	*_redirection_finder(char **dest, char **redirection, char **save)
{
	char	*find_ptr;
	char	*forefront;
	int		i;

	forefront = NULL;
	find_ptr = NULL;
	i = -1;
	while (redirection[++i] != NULL)
	{
		find_ptr = ft_strnstr(*dest, redirection[i], ft_strlen(*dest));
		printf("find_ptr : %s\n", find_ptr);
		if (find_ptr != NULL && (forefront == NULL || forefront > find_ptr))
		{
			forefront = find_ptr;
			*save = redirection[i];
			// printf("%s\n", *save);
		}
	}
	printf("asdsd %s\n", *save);
	if (forefront != NULL)
		*dest = forefront + 1;
	return (forefront);
}
