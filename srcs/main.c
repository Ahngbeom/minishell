/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2021/12/16 15:07:04 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	minishell_init(int argc, char *argv[], char *env[])
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
}

static	void	minishell_finalize()
{
	free(g_data.home_path);
	free(g_data.pwd);
	free(g_data.prompt);
}

int	main(int argc, char *argv[], char *env[])
{
	minishell_init(argc, argv, env);
	while (1)
	{
		if (minishell() != 0)
			break ;
	}
	minishell_finalize();
	return (0);
}
