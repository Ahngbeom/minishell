/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:20:29 by bahn              #+#    #+#             */
/*   Updated: 2021/12/12 13:34:55 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	enclosed_quotes(char *str)
{
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (0);
	else if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		return (0);
	else
		return (1);
}

static	void	then_input(int index)
{
	char	*input;
	char	*temp;

	while (enclosed_quotes(g_data.argv[index]))
	{
		input = readline("> ");
		temp = ft_strjoin(g_data.argv[index], "\n");
		g_data.argv[index] = ft_strjoin(temp, input);
		free(temp);
		free(input);
	}	
	input = ft_strtrim(g_data.argv[index], "\"");
	free(g_data.argv[index]);
	g_data.argv[index] = input;
}

int	double_quotation(void)
{
	char	*temp;

	if (argv_counter(g_data.argv) <= 1 && argv_counter(g_data.argv) > 3)
		return (0);
	else if (argv_counter(g_data.argv) == 2)
	{
		if (g_data.argv[1][0] == '$')
		{
			temp = ft_strtrim(g_data.argv[1], "$");
			// free(g_data.argv[1]);
			// g_data.argv[1] = getenv(temp);
			printf("%s\n", getenv(temp));
			free(temp);
			return (-1);
		}
	}
	else if (argv_counter(g_data.argv) == 2 && \
				(g_data.argv[1][0] != '\'' && g_data.argv[1][0] != '\"'))
		return (0);
	else if (!ft_strncmp(g_data.argv[1], "-n", ft_strlen(g_data.argv[1])))
		then_input(2);
	else
		then_input(1);
	return (0);
}
