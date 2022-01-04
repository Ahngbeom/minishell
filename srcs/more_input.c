/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:33:46 by bahn              #+#    #+#             */
/*   Updated: 2022/01/04 22:24:17 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*more_input(char *input)
{
	char	*ptr;
	char	*more;
	char	*tmp;

	ptr = input;
	if (ft_strchr(ptr, '\'') != NULL && (ft_strchr(ptr, '\'') == ft_strrchr(ptr, '\'')))
	{
		while (ft_strchr(ptr, '\'') >= ft_strrchr(ptr, '\''))
		{
			more = readline("> ");
			tmp = ptr;
			ptr = ft_strjoin(ptr, more);
			free(tmp);
			free(more);
		}
	}
	else if (ft_strchr(ptr, '\"') != NULL && (ft_strchr(ptr, '\"') < ft_strrchr(ptr, '\"')))
	{
		while (ft_strchr(ptr, '\"') >= ft_strrchr(ptr, '\"'))
		{
			more = readline("> ");
			tmp = ptr;
			ptr = ft_strjoin(ptr, more);
			free(tmp);
			free(more);
		}
	}
	if (input != NULL)
		free(input);
	return (ptr);
}
