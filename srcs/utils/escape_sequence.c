/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_sequence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:32:31 by bahn              #+#    #+#             */
/*   Updated: 2021/12/27 14:52:29 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*escape_sequence(char *arg)
{
	char	*find;
	char	*more_input;
	char	*result;
	char	*temp;

	find = ft_strchr(arg, '\\');
	if (find)
	{
		if (*(find + 1) == '\0')
		{
			while (find)
			{
				more_input = readline("> ");
				temp = ft_substr(arg, 0, find - arg);
				result = ft_strjoin(temp, more_input);
				free(temp);
				free(more_input);
				find = ft_strchr(result, '\\');
			}
		}
		else
		{
			while (find)
			{
				temp = ft_substr(arg, 0, find - arg);
				more_input = ft_substr(find, 1, ft_strlen(find) - 1);
				result = ft_strjoin(temp, more_input);
				free(temp);
				free(more_input);
				find = ft_strchr(result, '\\');
			}
		}
		return (result);
	}
	else
	{
		return (arg);
	}
}