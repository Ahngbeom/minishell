/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2021/12/09 17:42:21 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

char	*prompt(void)
{
	// ft_putstr_fd("minishell > ", STDOUT_FILENO);
	// g_data.input = readline("minishell 🚀 ");
	return ("minishell > ");
}

char	**set_env(int argc, char *argv[], char *env[])
{
	char	**env_dupl;
	int		env_len;
	int		i;

	if (argc != 1)
		exit(EXIT_FAILURE);
	(void)argv;
	env_len = 0;
	while (env[env_len] != NULL)
		env_len++;
	env_dupl = (char **)malloc(sizeof(char *) * env_len + 1);
	if (env_dupl == NULL)
		exit(EXIT_FAILURE);
	i = -1;
	while (env[++i] != NULL)
	{
		env_dupl[i] = ft_strdup(env[i]);
	}
	env_dupl[i] = NULL;
	return (env_dupl);
}

// int	main(int argc, char *argv[], char *env[])
// {
// 	g_data.input = NULL;
// 	g_data.log = malloc(sizeof(t_log));
// 	g_data.env = set_env(argc, argv, env);
// 	// signal(SIGINT, signal_handler);
// 	// signal(SIGQUIT, signal_handler);
// 	// tcgetattr(STDIN_FILENO, &g_data.org_term);
// 	// tcgetattr(STDIN_FILENO, &g_data.msh_term);
// 	// g_data.msh_term.c_lflag &= ~(ICANON | ECHOCTL);
// 	// g_data.msh_term.c_cc[VMIN] = 1;
// 	// g_data.msh_term.c_cc[VTIME] = 0;
// 	// tcsetattr(STDIN_FILENO, TCSANOW, &g_data.msh_term);
// 	while (1)
// 	{
// 		prompt();
// 		if (keyinput_controller2() == 1)
// 		{
// 			ft_putendl_fd("exit", 1);
// 			break ;
// 		}
// 		ft_putendl_fd(NULL, 1);
// 		add_history(g_data.input);
// 	}
// 	free(g_data.input);
// 	free(g_data.log);
// 	tcsetattr(STDIN_FILENO, TCSANOW, &g_data.org_term);
// 	return (0);
// }

int	main(int argc, char *argv[], char *env[])
{
	g_data.input = NULL;
	g_data.env = set_env(argc, argv, env);
	// signal(SIGINT, signal_handler);
	// signal(SIGQUIT, signal_handler);
	tcgetattr(STDIN_FILENO, &g_data.org_term);
	tcgetattr(STDIN_FILENO, &g_data.msh_term);
	g_data.msh_term.c_lflag &= ~(ICANON | ECHOCTL);
	g_data.msh_term.c_cc[VMIN] = 1;
	g_data.msh_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_data.msh_term);
	while (1)
	{
		if (minishell() != 0)
			break ;
	}
	free(g_data.log);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_data.org_term);
	return (0);
}
