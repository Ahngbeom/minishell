/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:33:46 by bahn              #+#    #+#             */
/*   Updated: 2022/01/05 13:20:11 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	more_input(char **input)
{
	char	*ptr;
	char	*more;
	char	*tmp;

	ptr = *input;
	if (ft_strchr(ptr, '\'') != NULL && (ft_strchr(ptr, '\'') == ft_strrchr(ptr, '\'')))
	{
		while (ft_strchr(ptr, '\'') == ft_strrchr(ptr, '\''))
		{
			more = readline("> ");
			tmp = ptr;
			ptr = ft_strjoin(ptr, "\n");
			free(tmp);
			tmp = ptr;
			ptr = ft_strjoin(ptr, more);
			free(tmp);
			printf("new input : %s\n", ptr);
			free(more);
		}
	}
	else if (ft_strchr(ptr, '\"') != NULL && (ft_strchr(ptr, '\"') == ft_strrchr(ptr, '\"')))
	{
		while (ft_strchr(ptr, '\"') == ft_strrchr(ptr, '\"'))
		{
			more = readline("> ");
			tmp = ptr;
			ptr = ft_strjoin(ptr, "\n");
			free(tmp);
			tmp = ptr;
			ptr = ft_strjoin(ptr, more);
			free(tmp);
			free(more);
		}
	}
	if (ptr != *input && *input != NULL)
	{
		free(*input);
		*input = ptr;
	}
}
