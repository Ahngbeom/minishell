/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:40:55 by bahn              #+#    #+#             */
/*   Updated: 2022/01/23 03:27:53 by bahn             ###   ########.fr       */
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

void	set_type(t_command *command, char **sentence)
{
	int		i;
	char	*find;
	char	*temp;

	i = -1;
	find = NULL;
	while (g_data.arr_redirect[++i] != NULL)
	{
		find = ft_strnstr(*sentence, g_data.arr_redirect[i], \
							ft_strlen(*sentence));
		if (find)
		{
			command->type = g_data.arr_redirect[i];
			temp = *sentence;
			*sentence = ft_substr(*sentence, 0, find - *sentence);
			free(temp);
			return ;
		}
	}
}
