/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abbreviation_converter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:55:52 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 10:41:14 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	eqsign_converter(char **arg, char *eqsign_ptr, char *tilde_ptr)
{
	char	**split;
	char	*prev_str;
	char	*temp;

	split = ft_split(*arg, *eqsign_ptr);
	if (envv_name_format_checker(split[0]) && *(split[1]) != '~')
		return ;
	split_free(split);
	prev_str = ft_strjoin_with_free(\
				ft_substr(*arg, 0, tilde_ptr - *arg), \
				ft_strdup(get_envv_value("HOME")));
	temp = *arg;
	*arg = ft_strjoin_with_free(prev_str, \
				ft_substr(tilde_ptr, 1, ft_strlen(*arg)));
	free(temp);
}

static void	tilde_converter(char **arg, char *tilde_ptr)
{
	char	*temp;

	if (ft_strlen(*arg) == 1)
	{
		free(*arg);
		*arg = ft_strdup(get_envv_value("HOME"));
	}
	else
	{
		if (*(tilde_ptr + 1) == '/')
		{
			temp = *arg;
			*arg = ft_strjoin_with_free(\
					ft_strdup(get_envv_value("HOME")), \
						ft_strdup(tilde_ptr + 1));
			free(temp);
		}
	}
}

static void	tilde_checker(char **arg)
{
	char	*tilde;
	char	*eq_sign;

	tilde = ft_strchr(*arg, '~');
	eq_sign = ft_strchr(*arg, '=');
	if (tilde != NULL)
	{
		if (tilde == *arg)
		{
			tilde_converter(arg, tilde);
		}
		else if (eq_sign && *arg != eq_sign)
			eqsign_converter(arg, eq_sign, tilde);
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
			tilde_checker(&command->argv[i]);
		ptr = ptr->next;
	}
	g_data.not_convert = 0;
}
