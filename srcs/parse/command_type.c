/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:40:55 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 01:24:57 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*type_finder(char *str, int *length, char **input)
{
	char	*find;
	int		i;

	i = -1;
	while (g_data.arr_redirect[++i] != NULL)
	{
		if (input != NULL)
			find = ft_strnstr(str, g_data.arr_redirect[i], \
								ft_strlen(g_data.arr_redirect[i]));
		else
			find = ft_strnstr(str, g_data.arr_redirect[i], \
								ft_strlen(str));
		if (find)
		{
			if (length != NULL)
				*length = (find + ft_strlen(g_data.arr_redirect[i])) - *input;
			return (find);
		}
	}
	return (NULL);
}

void	set_type(t_command *command, char **sentence)
{
	int		i;
	char	*find;

	i = -1;
	find = NULL;
	while (g_data.arr_redirect[++i] != NULL)
	{
		find = ft_strnstr(*sentence, g_data.arr_redirect[i], \
							ft_strlen(g_data.arr_redirect[i]));
		if (find)
		{
			command->type = g_data.arr_redirect[i];
			return ;
		}
	}
}
