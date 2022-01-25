/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:43:32 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 19:32:57 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	envv_enclosed_quotes_checker(char *arg)
// {
// 	char	envv_mark;
// 	char	*sq_quotes;
// 	char	*next_sq_quotes;
// 	char	*db_quotes;

// 	envv_mark = ft_strchr(arg, '$');
// 	if (envv_mark)
// 	{
// 		sq_quotes = ft_strchr(arg, '\'');
// 		if (!sq_quotes)
// 			return (1);
// 		next_sq_quotes = ft_strchr(sq_quotes + 1, '\'');
// 		db_quotes = ft_strchr(arg, '\'');
// 		if (db_quotes)
// 		{
			
// 		}
		
// 	}
// 	return (0);
// }

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
	temp = ft_strjoin_with_free(pre_str, quotes_str);
	*arg = ft_strjoin_with_free(temp, next_str);
	if (quotes == '\"')
		envmark_converter(arg);
}

static void	quotes_checker(char **arg)
{
	char	*sg_quotes;
	char	*db_quotes;

	printf("arg : %s\n", *arg);
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
