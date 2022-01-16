/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2022/01/17 01:05:04 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	minishell_init(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	g_data.org_envv = env;
	g_data.envv = set_lstenvv(env);
	g_data.envv_path = set_envvpath();
	g_data.commands = NULL;
	set_redirection();
	g_data.exit_stat = ft_itoa(0);
	g_data.pipe = malloc(sizeof(int) * 2);
	g_data.input = ft_strdup("input");
	g_data.output = ft_strdup("output");
	set_termios();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	minishell_finalize(void)
{
	free(g_data.prompt);
	ft_lstclear(g_data.envv, free);
	// split_free(g_data.arr_redirect);
	split_free(g_data.envv_path);
	free(g_data.pipe);
	unlink(g_data.input);
	unlink(g_data.output);
	free(g_data.input);
	free(g_data.output);
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

	input = NULL;
	minishell_init(argc, argv, env);
	while (1)
	{
		input = readline(prompt());
		check = preprocess(input);
		if (check == 0)
		{
			input = more_input(input);
			add_history(input);
			minishell(&input);
			free(input);
			input = NULL;
		}
		else if (check < 0)
			break ;
	}
	minishell_finalize();
	return (ft_atoi(g_data.exit_stat));
}
// system("leaks minishell > leaks_result && cat leaks_result && rm -rf leaks_result");
