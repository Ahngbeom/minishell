/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abbreviation_converter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:55:52 by bahn              #+#    #+#             */
/*   Updated: 2022/01/17 23:31:29 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tilde_converter(char **arg)
{
	char	*find;
	char	*temp;

	find = ft_strchr(*arg, '~');
	if (find != NULL && find == *arg)
	{
		if (ft_strlen(*arg) == 1)
		{
			free(*arg);
			*arg = ft_strdup(get_envv_value("HOME"));
		}
		else
		{
			if (*(find + 1) == '/')
			{
				temp = ft_substr(find + 1, 0, ft_strlen(find + 1));
				free(*arg);
				*arg = ft_strjoin(get_envv_value("HOME"), temp);
				free(temp);
			}
		}
	}
}

void	abbreviation_converter(t_list *list)
{
	t_list		*ptr;
	t_command	*command;
	int			i;

	ptr = list;
	while (ptr != NULL)
	{
		command = ptr->content;
		i = -1;
		while (command->argv[++i] != NULL)
		{
			tilde_converter(&command->argv[i]);
			envmark_converter(&command->argv[i]);
		}
		ptr = ptr->next;
	}
}
