/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_sequence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:32:31 by bahn              #+#    #+#             */
/*   Updated: 2021/12/27 17:50:12 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*escape_sequence(char *arg)
{
	char	*ptr;
	char	*find;
	char	*more_input;
	char	*result;
	char	*temp;

	result = NULL;
	find = ft_strchr(arg, '\\');
	if (find)
	{
		ptr = arg;
		while (find)
		{
			if (*(find + 1) == '\0')
			{
				more_input = readline("> ");
				temp = ft_substr(ptr, 0, ft_strlen(arg) - ft_strlen(find));
				result = ft_strjoin(temp, more_input);
				free(temp);
				free(more_input);
				ptr = result;
				find = ft_strchr(ptr, '\\');
			}
			else
			{
				temp = ft_substr(ptr, 0, ft_strlen(arg) - ft_strlen(find));
				more_input = ft_substr(find, 1, ft_strlen(find) - 1);
				result = ft_strjoin(temp, more_input);
				free(temp);
				free(more_input);
				find = ft_strchr(result + ft_strlen(result) - ft_strlen(more_input), '\\');
			}
		}
		// free(arg);
		return (result);
	}
	else
	{
		return (arg);
	}
}