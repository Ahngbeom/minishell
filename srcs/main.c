/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 20:23:27 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	minishell_init(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	g_data.lst_env = set_lstenvv(env);
	increase_shlvl();
	g_data.envv_path = set_envvpath();
	g_data.lst_cmds = NULL;
	set_redirection();
	g_data.exit_stat = ft_itoa(0);
	set_termios();
}

void	minishell_finalize(void)
{
	free(g_data.prompt);
	ft_lstclear(&g_data.lst_env, hash_free);
	split_free(g_data.envv_path);
	free(g_data.arr_redirect);
}

static	int	preprocess(char **input)
{
	*input = ft_strtrim_with_free(*input, " ");
	if (exit_checker(*input))
		return (-1);
	if (ft_strlen(*input) == 0)
	{
		if (*input != NULL)
			free(*input);
		return (1);
	}
	if (syntax_checker(*input))
		return (1);
	add_history(*input);
	return (0);
}

static int	parsing(char *input)
{
	if (split_2_command(&g_data.lst_cmds, input) == -1)
		return (1);
	exit_status_switch(0);
	abbreviation_converter(g_data.lst_cmds);
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
		signal(SIGQUIT, signal_handler);
		input = readline(prompt());
		check = preprocess(&input);
		if (check < 0)
			break ;
		if (check == 0 && !parsing(input))
			minishell();
	}
	minishell_finalize();
	return (ft_atoi(g_data.exit_stat));
}
