/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:43:32 by bahn              #+#    #+#             */
/*   Updated: 2022/01/26 13:24:36 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quotes_compose(char **arg, char *quotes_ptr, char quotes)
{
	char	*next_quotes;
	char	*pre_str;
	char	*next_str;
	char	*quotes_str;
	char	*temp;

	next_quotes = ft_strchr(quotes_ptr + 1, quotes);
	pre_str = ft_substr(*arg, 0, quotes_ptr - *arg);
	next_str = ft_strdup(next_quotes + 1);
	quotes_str = ft_substr(quotes_ptr, 1, next_quotes - quotes_ptr - 1);
	if (quotes == '\"' && \
		(!ft_strchr(*arg, '\'') || \
		(quotes_ptr > ft_strchr(*arg, '\'') && \
		next_quotes > ft_strchr(*arg, '\'')) || \
		(quotes_ptr < ft_strchr(*arg, '\'') && \
		next_quotes < ft_strchr(*arg, '\''))))
		envmark_converter(&quotes_str);
	temp = ft_strjoin_with_free(pre_str, quotes_str);
	free(*arg);
	*arg = ft_strjoin_with_free(temp, next_str);
}

static void	quotes_checker(char **arg)
{
	char	*sg_quotes;
	char	*db_quotes;

	sg_quotes = ft_strchr(*arg, '\'');
	db_quotes = ft_strchr(*arg, '\"');
	if (!sg_quotes && !db_quotes)
		envmark_converter(arg);
	else
	{
		while (sg_quotes || db_quotes)
		{
			if (db_quotes)
				quotes_compose(arg, db_quotes, '\"');
			else if (sg_quotes)
				quotes_compose(arg, sg_quotes, '\'');
			sg_quotes = ft_strchr(*arg, '\'');
			db_quotes = ft_strchr(*arg, '\"');
		}
	}
}

void	remove_quotes(t_command *command)
{
	int		i;

	i = -1;
	while (command->argv[++i] != NULL)
	{
		quotes_checker(&command->argv[i]);
	}	
}
