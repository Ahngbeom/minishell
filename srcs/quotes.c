/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:20:29 by bahn              #+#    #+#             */
/*   Updated: 2021/12/11 22:30:59 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	enclosed_quotes(char *str)
{
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (0);
	else if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		return (0);
	else
		return (1);
}

void	then_input(int index)
{
	char	*input;
	char	*temp;

	while (enclosed_quotes(g_data.argv[index]))
	{
		input = readline("> ");
		temp = ft_strdup(g_data.argv[index]);
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
	if (argv_counter(g_data.argv) <= 1 && argv_counter(g_data.argv) > 3)
		return (0);
	else if (argv_counter(g_data.argv) > 1 && \
				!ft_strncmp(g_data.argv[1], "-n", ft_strlen(g_data.argv[1])))
		then_input(2);
	else
		then_input(1);
	return (0);
}
