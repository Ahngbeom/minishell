/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:33:46 by bahn              #+#    #+#             */
/*   Updated: 2022/01/07 15:00:47 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*quotes_process(char *input, char quotes)
{
	char	*more;
	char	*result;
	char	*tmp;

	result = input;
	while (ft_strchr(result, quotes) == ft_strrchr(result, quotes))
	{
		more = readline("> ");
		tmp = result;
		result = ft_strjoin(result, "\n");
		free(tmp);
		tmp = result;
		result = ft_strjoin(result, more);
		free(tmp);
		free(more);
	}
	return (result);
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

static int	backslash_checker(char **input)
{
	char	*find;

	find = ft_strchr(*input, '\\');
	if (find != NULL && *(find + 1) == '\0')
		return (1);
	else
		return (0);
}

void	more_input(char **input)
{
	char	*more;
	char	*tmp;

	if (quotes_checker(*input, '\''))
		*input = quotes_process(*input, '\'');
	else if (quotes_checker(*input, '\"'))
		*input = quotes_process(*input, '\"');
	else if (backslash_checker(input))
	{
		while (1)
		{
			more = readline("> ");
			if (ft_strncmp(more, "\\", ft_strlen(more) + 1))
			{
				tmp = ft_substr(*input, 0, ft_strchr(*input, '\\') - *input);
				free(*input);
				*input = ft_strjoin(tmp, more);
				free(tmp);
				break ;
			}
			free(more);
		}
	}
}
