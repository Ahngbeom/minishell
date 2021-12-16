/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:20:29 by bahn              #+#    #+#             */
/*   Updated: 2021/12/16 14:33:49 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	enclosed_quotes_checker(char *str, char start_quotes)
{
	if (str[0] == start_quotes && str[ft_strlen(str) - 1] == start_quotes)
		return (0);
	else
		return (1);
}

int	then_input(int index, char start_quotes)
{
	char	*input;
	char	*temp;

	while (enclosed_quotes_checker(g_data.argv[index], start_quotes))
	{
		input = readline("> ");
		temp = ft_strjoin(g_data.argv[index], "\n");
		g_data.argv[index] = ft_strjoin(temp, input);
		free(temp);
		free(input);
	}
	temp = malloc(sizeof(char) + 1);
	temp[0] = start_quotes;
	temp[1] = '\0';
	input = ft_strtrim(g_data.argv[index], temp);
	free(temp);
	free(g_data.argv[index]);
	g_data.argv[index] = input;
	// return (envvar_checker());
	return (0);
}

char	quotes_counter(char *str)
{
	char	quotes;
	int		i;

	printf("quotes counter\n");
	quotes = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (quotes == str[i])
			quotes = 0;
		if (str[i] == '\'' || str[i] == '\"')
			quotes = str[i];
	}
	printf("%c\n", quotes);
	return (quotes);
}
