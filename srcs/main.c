/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2022/01/21 14:17:18 by minsikim         ###   ########.fr       */
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

static	int	preprocess(char **input)
{
	char	*temp;

	temp = *input;
	*input = ft_strtrim(*input, " ");
	free(temp);
	if (*input == NULL || !ft_strncmp(*input, "exit", ft_strlen("exit") + 1))
	{
		ft_putendl_fd("exit", 1);
		if (*input != NULL)
			free(*input);
		return (-1);
	}
	if (ft_strlen(*input) == 0)
	{
		if (*input != NULL)
			free(*input);
		return (1);
	}
	if (!ft_isalnum(**input) && ft_isprint(**input) && **input != '$')
	{
		printf("minishell: syntax error near unexpected token `%c'\n", **input);
		add_history(*input);
		if (*input != NULL)
			free(*input);
		return (1);
	}
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
		if (check == 0)
		{
			input = more_input(input);
			add_history(input);
			// printf("argv:%s %s\n", ((t_command *)g_data.commands->content)->argv[0], ((t_command *)g_data.commands->content)->argv[1]); //////////
			input_split(&g_data.commands, input); // deleted '?
			
			// split_2_command(&g_data.commands, input);
			// free(input);
			// continue ;
			
			free(input);
			abbreviation_converter(g_data.commands);
			print_info(g_data.commands, 0);
			// printf("argv:%s %s\n", ((t_command *)g_data.commands->content)->argv[0], ((t_command *)g_data.commands->content)->argv[1]); // argv test
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
