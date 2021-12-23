/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2021/12/23 13:37:10 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	minishell_init(int argc, char *argv[], char *env[])
{
	if (argc != 1)
		exit(EXIT_FAILURE);
	(void)argv;
	g_data.org_env = env;
	g_data.envv = set_lstenv(env);
	if (g_data.home_path == NULL)
		g_data.home_path = getcwd(NULL, 0);
	if (chdir(getenv("HOME")) == -1)
		exit(errno);
	g_data.command = NULL;
	g_data.command2 = NULL;
	g_data.arr_redirect = ft_calloc(sizeof(char *), 7);
	g_data.arr_redirect[0] = ft_strdup(";");
	g_data.arr_redirect[1] = ft_strdup(">>");
	g_data.arr_redirect[2] = ft_strdup("<<");
	g_data.arr_redirect[3] = ft_strdup(">");
	g_data.arr_redirect[4] = ft_strdup("<");
	g_data.arr_redirect[5] = ft_strdup("|");
	g_data.pipe = malloc(sizeof(int) * 2);
}

static	void	minishell_finalize()
{
	ft_lstclear(g_data.envv, free);
	split_free(g_data.argv);
	split_free(g_data.arr_redirect);
	free(g_data.output);
	free(g_data.pipe);
	free(g_data.home_path);
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
	// system("leaks minishell > leaks_result && cat leaks_result && rm -rf leaks_result");
	return (0);
}
