/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2021/12/17 11:29:27 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	rtn;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	g_data.input = readline(prompt());
	if (g_data.input != NULL)
	{
		if (!ft_strncmp(g_data.input, "\n", ft_strlen(g_data.input)))
			return (0);
		else if (!ft_strncmp(g_data.input, "exit", ft_strlen(g_data.input) + 1))
		{
			ft_putendl_fd("exit", 1);
			return (1);
		}
		rtn = parsing();
		if (rtn < 0)
			printf("%s: command not found\n", g_data.argv[0]);
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
