/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2021/12/21 17:24:51 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(void)
{
	int		i;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	g_data.input = readline(prompt());
	if (g_data.input == NULL)
	{
		ft_putendl_fd("exit", 1);
		return (1);
	}
	pipe(g_data.pipe);
	g_data.split_input = ft_split(g_data.input, ';');
	i = -1;
	while (g_data.split_input[++i] != NULL)
	{
		if (!ft_strncmp(g_data.split_input[i], "\n", ft_strlen("\n") + 1))
			return (0);
		else if (!ft_strncmp(g_data.split_input[i], "exit", ft_strlen("exit") + 1))
		{
			if (g_data.split_input[i][4] == ' ' || !(g_data.split_input[i][4]))
				ft_putendl_fd("exit", 1);
			if (g_data.input[5]) // && counter(split_input) == 1
				printf("minishell: exit: %s: numeric argument required\n", g_data.split_input[i] + 5);
			return (1);
		}
		parsing(g_data.split_input[i]);
		// free(g_data.split_input[i]);
		// split_free(g_data.argv);
	}
	read(g_data.pipe[0], g_data.output, sizeof(g_data.output));
	printf("%s", g_data.output);
	add_history(g_data.input);
	return (0);
}
