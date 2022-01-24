/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:33:46 by bahn              #+#    #+#             */
/*   Updated: 2022/01/11 22:22:18 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quotes_process(char quotes, char **result)
{
	char	*more;
	char	*tmp;

	while (ft_strchr(*result, quotes) == ft_strrchr(*result, quotes))
	{
		more = readline("> ");
		tmp = *result;
		*result = ft_strjoin(*result, "\n");
		free(tmp);
		tmp = *result;
		*result = ft_strjoin(*result, more);
		free(tmp);
		free(more);
	}
}

static void	backslash_process(char **result)
{
	char	*more;
	char	*tmp;

	while (1)
	{
		more = readline("> ");
		if (ft_strncmp(more, "\\", ft_strlen(more) + 1))
		{
			tmp = ft_substr(*result, 0, ft_strchr(*result, '\\') - *result);
			free(*result);
			*result = ft_strjoin(tmp, more);
			free(tmp);
			break ;
		}
		free(more);
	}
}

static int	quotes_checker(char *input, char quotes)
{
	char	*find;

	find = ft_strchr(input, quotes);
	if (find != NULL && \
		find == ft_strrchr(input, quotes) && \
		*(find - 1) != '\\')
		return (quotes);
	else
		return (0);
}

static int	backslash_checker(char *input)
{
	char	*find;

	find = ft_strchr(input, '\\');
	if (find != NULL && *(find + 1) == '\0')
		return (1);
	else
		return (0);
}

char	*more_input(char *input)
{
	char	*result;

	result = input;
	while (1)
	{
		if (quotes_checker(result, '\''))
			quotes_process('\'', &result);
		else if (quotes_checker(input, '\"'))
			quotes_process('\"', &result);
		else if (backslash_checker(input))
			backslash_process(&result);
		else
			break ;
	}
	return (result);
}
