/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2022/01/05 18:54:22 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	minishell_init(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	g_data.org_envv = env;
	g_data.envv = set_lstenvv(env);
	set_envvpath();
	g_data.commands = NULL;
	set_redirection();
	g_data.status = 0;
	g_data.pipe = malloc(sizeof(int) * 2);
	set_termios();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	minishell_finalize(void)
{
	ft_lstclear(g_data.envv, free);
	split_free(g_data.arr_redirect);
	free(g_data.pipe);
	free(g_data.prompt);
}

static	int	preprocess(char *input)
{
	char	*trim;

	trim = ft_strtrim(input, " ");
	if (trim == NULL || !ft_strncmp(trim, "exit", ft_strlen("exit") + 1))
	{
		ft_putendl_fd("exit", 1);
		if (input != NULL)
			free(input);
		if (trim != NULL)
			free(trim);
		return (-1);
	}
	else if (ft_strlen(trim) == 0)
	{
		if (input != NULL)
			free(input);
		if (ft_strlen(trim) > 0)
			free(trim);
		return (1);
	}
	else
		return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*input;
	int		check;

	minishell_init(argc, argv, env);
	while (1)
	{
		
		input = readline(prompt());
		check = preprocess(input);
		if (check == 0)
			minishell(input);
		else
		{
			if (check < 0)
				break ;
		}
	}
	minishell_finalize();
	
	// system("leaks minishell > leaks_result && cat leaks_result && rm -rf leaks_result");
	
	return (g_data.status);
}
