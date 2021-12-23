/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2021/12/23 13:58:42 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(void)
{
	int		i;
	t_list		*ptr;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	g_data.input = readline(prompt());
	if (g_data.input == NULL || !ft_strncmp(g_data.input, "exit", ft_strlen(g_data.input) + 1))
	{
		ft_putendl_fd("exit", 1);
		return (1);
	}
	add_history(g_data.input);
	ft_split_command(&g_data.command2, ft_strtrim(g_data.input, " "), g_data.arr_redirect);
	ptr = g_data.command2;
	while (ptr != NULL)
	{
		parsing(ptr);
		ptr = ptr->next;
	}
	ft_lstclear(&g_data.command2, command_free);
	// pipe(g_data.pipe);
	
	// i = -1;
	// while (g_data.command->split_input[++i] != NULL)
	// {
	// 	if (!ft_strncmp(g_data.command->split_input[i], "\n", ft_strlen("\n") + 1))
	// 		return (0);
	// 	else if (!ft_strncmp(g_data.command->split_input[i], "exit", ft_strlen("exit") + 1))
	// 	{
	// 		if (g_data.command->split_input[i][4] == ' ' || !(g_data.command->split_input[i][4]))
	// 			ft_putendl_fd("exit", 1);
	// 		if (g_data.input[5]) // && counter(split_input) == 1
	// 			printf("minishell: exit: %s: numeric argument required\n", g_data.command->split_input[i] + 5);
	// 		return (1);
	// 	}
	// 	parsing(g_data.command->split_input[i]);
	// 	// free(g_data.split_input[i]);
	// 	// split_free(g_data.argv);
	// }
	// close(g_data.pipe[0]);
	// close(g_data.pipe[1]);
	// add_history(g_data.input);
	return (0);
}
