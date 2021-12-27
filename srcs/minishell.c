/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2021/12/27 17:59:38 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(void)
{
	char		*input;
	t_list		*ptr;
	
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	input = readline(prompt());
	if (input == NULL || !ft_strncmp(input, "exit", ft_strlen(input) + 1))
	{
		ft_putendl_fd("exit", 1);
		return (1);
	}
	input = escape_sequence(input);
	add_history(input);
	ft_split_command(&g_data.commands, ft_strtrim(input, " "), g_data.arr_redirect);
	free(input);
	ptr = g_data.commands;
	while (ptr != NULL)
	{
		parsing(((t_command *)ptr->content));
		if (!((t_command *)ptr->content)->bulit_in_flag)
			to_execve(((t_command *)ptr->content));
		ptr = ptr->next;
	}
	ft_lstclear(&g_data.commands, command_free);
	return (0);
}
