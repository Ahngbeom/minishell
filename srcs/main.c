/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2022/01/19 23:34:17 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	minishell_init(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	g_data.lst_env = set_lstenvv(env);
	// set_history(g_data.lst_env);
	g_data.envv_path = set_envvpath();
	g_data.commands = NULL;
	set_redirection();
	g_data.exit_stat = ft_itoa(0);
	set_termios();
	// signal(SIGINT, signal_handler);
	// signal(SIGQUIT, SIG_IGN);
}

void	minishell_finalize(void)
{
	free(g_data.prompt);
	ft_lstclear(&g_data.lst_env, hash_free);
	split_free(g_data.envv_path);
	free(g_data.arr_redirect);
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
	free(trim);
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
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);input = readline(prompt());
		check = preprocess(input);
		if (check == 0)
		{
			input = more_input(input);
			add_history(input);
			input_split(&g_data.commands, input);
			free(input);
			abbreviation_converter(g_data.commands);
			print_info(g_data.commands, 0);
			
			minishell();
		}
		else if (check < 0)
			break ;
		// system("leaks minishell > leaks_result && cat leaks_result && rm -rf leaks_result");
	}
	minishell_finalize();
	// system("leaks minishell > leaks_result && cat leaks_result && rm -rf leaks_result");
	return (ft_atoi(g_data.exit_stat));
}
