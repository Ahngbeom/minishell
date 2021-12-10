/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2021/12/10 17:16:34 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	split_free(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}

int	minishell(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	g_data.input = readline(prompt());
	if (g_data.input != NULL)
	{
		if (ft_strncmp(g_data.input, "\n", ft_strlen(g_data.input)) == 0)
			return (0);
		if (parsing())
			printf("%s: command not found\n", g_data.input);
		add_history(g_data.input);
		free(g_data.input);
		split_free(g_data.argv);
		return (0);
	}
	else
	{
		ft_putendl_fd("exit", 1);
		return (1);
	}
}
