/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2021/12/21 15:20:45 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	minishell_init(int argc, char *argv[], char *env[])
{
	if (argc != 1)
		exit(EXIT_FAILURE);
	(void)argv;
	// execve 함수로 인해 프로세스가 교체되었을 경우 g_data.argv 흔적을 찾아 수행한 명령어 history에 추가
	if (g_data.argv != NULL)
		add_history(g_data.argv[0]);
	g_data.org_env = env;
	g_data.envv = set_env(env);
	if (g_data.cmd_path != NULL)
		free(g_data.cmd_path);
	if (g_data.home_path == NULL)
		g_data.home_path = getcwd(NULL, 0);
	if (chdir(getenv("HOME")) == -1)
		exit(errno);
	g_data.current_path = getcwd(NULL, 0);
}

static	void	minishell_finalize()
{
	ft_lstclear(g_data.envv, free);
	split_free(g_data.argv);
	split_free(g_data.split_input);
	free(g_data.home_path);
	free(g_data.current_path);
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
	system("leaks minishell > leaks_result && cat leaks_result && rm -rf leaks_result");
	return (0);
}
