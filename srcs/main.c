/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2021/12/28 12:16:41 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	set_redirection(void)
{
	g_data.arr_redirect = ft_calloc(sizeof(char *), 7);
	g_data.arr_redirect[0] = ft_strdup(";");
	g_data.arr_redirect[1] = ft_strdup(">>");
	g_data.arr_redirect[2] = ft_strdup("<<");
	g_data.arr_redirect[3] = ft_strdup(">");
	g_data.arr_redirect[4] = ft_strdup("<");
	g_data.arr_redirect[5] = ft_strdup("|");
}

static	void	set_envvpath_list(void)
{
	int		i;
	char	*temp;

	g_data.envv_path = ft_split(getenv("PATH"), ':');
	i = -1;
	while (g_data.envv_path[++i] != NULL)
	{
		if (g_data.envv_path[i][ft_strlen(g_data.envv_path[i]) - 1] != '/')
		{
			temp = g_data.envv_path[i];
			g_data.envv_path[i] = ft_strjoin(g_data.envv_path[i], "/");
			free(temp);
		}
	}
}

static	void	minishell_init(int argc, char *argv[], char *env[])
{
	if (argc != 1)
		exit(EXIT_FAILURE);
	(void)argv;
	g_data.org_envv = env;
	g_data.envv = set_lstenv(env);
	set_envvpath_list();
	if (chdir(getenv("HOME")) == -1)
		exit(errno);
	g_data.commands = NULL;
	set_redirection();
	g_data.pipe = malloc(sizeof(int) * 2);
}

void	minishell_finalize(void)
{
	ft_lstclear(g_data.envv, free);
	split_free(g_data.arr_redirect);
	free(g_data.pipe);
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
