/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2021/12/10 21:52:37 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

char	*prompt(void)
{
	char	*temp;

	g_data.prompt = ft_strjoin("\e[1;32mminishell\e[0m:", g_data.pwd);
	temp = ft_strdup(g_data.prompt);
	free(g_data.prompt);
	g_data.prompt = ft_strjoin(temp, "$ ");
	free(temp);
	// g_data.prompt = ft_strdup("minishell 🚀 ");
	return (g_data.prompt);
}

int	main(int argc, char *argv[], char *env[])
{
	g_data.input = NULL;
	g_data.env = set_env(argc, argv, env);
	g_data.pwd = getcwd(NULL, 0);
	while (1)
	{
		if (minishell() != 0)
			break ;
	}
	free_env(g_data.env);
	free(g_data.pwd);
	free(g_data.prompt);
	return (0);
}
