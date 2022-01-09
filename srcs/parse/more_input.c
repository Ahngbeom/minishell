/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:33:46 by bahn              #+#    #+#             */
/*   Updated: 2022/01/09 20:40:44 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quotes_process(char **input, char quotes)
{
	char	*more;
	char	*tmp;

	while (ft_strchr(*input, quotes) == ft_strrchr(*input, quotes))
	{
		more = readline("> ");
		tmp = *input;
		*input = ft_strjoin(*input, "\n");
		free(tmp);
		tmp = *input;
		*input = ft_strjoin(*input, more);
		free(tmp);
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
		quotes_process(input, '\'');
	else if (quotes_checker(*input, '\"'))
		quotes_process(input, '\"');
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
