/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2021/12/17 15:32:54 by minsikim         ###   ########.fr       */
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
		if (!ft_strncmp(g_data.input, "\n", ft_strlen("\n") + 1))
			return (0);
		else if (!ft_strncmp(g_data.input, "exit", ft_strlen("exit") + 1))
		{
			ft_putendl_fd("exit", 1);
			return (1);
		}
		rtn = parsing();
		if (rtn < 0)
			printf("%s: command not found\n", g_data.input);
		// else if (rtn == SELF_PROC)
		// {
			add_history(g_data.input);
			free(g_data.input);
		// }
		split_free(g_data.argv);
		return (0);
	}
	else
	{
		ft_putendl_fd("exit", 1);
		return (1);
	}
}
