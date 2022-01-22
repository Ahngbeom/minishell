/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:40:55 by bahn              #+#    #+#             */
/*   Updated: 2022/01/22 17:22:39 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*type_finder(char *str)
{
	char	*find;
	int		i;

	i = -1;
	while (g_data.arr_redirect[++i] != NULL)
	{
		find = ft_strnstr(str, g_data.arr_redirect[i], \
						ft_strlen(g_data.arr_redirect[i]));
		if (find)
			return (find);
	}
	return (NULL);
}

int	set_type(t_command *command, char *sentence)
{
	int		i;
	char	*find;
	int		type_len;

	type_len = 0;
	i = -1;
	find = NULL;
	while (g_data.arr_redirect[++i] != NULL)
	{
		find = ft_strnstr(sentence, g_data.arr_redirect[i], \
							ft_strlen(sentence));
		if (find)
		{
			command->type = g_data.arr_redirect[i];
			type_len = ft_strlen(g_data.arr_redirect[i]);
			break ;
		}
	}
	return (type_len);
}
