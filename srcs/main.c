/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2021/12/15 16:12:56 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (argc != 1)
		exit(EXIT_FAILURE);
	(void)argv;
	// g_data.env = set_env(argc, argv, env);
	g_data.env = env;
	if (g_data.bin_path != NULL)
		free(g_data.bin_path);
	g_data.bin_path = ft_strdup("/bin/");
	if (g_data.cmd_path != NULL)
		free(g_data.cmd_path);
	if (g_data.home_path == NULL)
		g_data.home_path = getcwd(NULL, 0);
	if (chdir(getenv("HOME")) == -1)
		exit(errno);
	g_data.pwd = getcwd(NULL, 0);
	while (1)
	{
		if (minishell() != 0)
			break ;
	}
	free(g_data.home_path);
	free(g_data.pwd);
	free(g_data.prompt);
	return (0);
}
