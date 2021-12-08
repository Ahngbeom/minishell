/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2021/12/09 01:18:35 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	prompt(void)
{
	ft_putstr_fd("minishell > ", STDOUT_FILENO);
	// g_data.input = readline("minishell 🚀 ");
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

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		prompt();
	}
}

int	proc_child()
{
	int	ch;
	int	idx;

	ch = 0;
	idx = -1;
	while (read(STDIN_FILENO, &ch, 1) > 0)
	{
		if (ch == EOT)
		{
			if (idx == -1)
				return (1);
			else
				continue ;
		}
		else if (ch == 127)
		{
			if (idx >= 0)
			{
				--idx;
				write(0, "\b \b", 3);
			}
		}
		else if (ch == LF)
			break ;
		else
		{
			++idx;
			write(0, &ch, 1);
		}
		ch = 0;
	}
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	g_data.env = set_env(argc, argv, env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	tcgetattr(STDIN_FILENO, &g_data.org_term);
	tcgetattr(STDIN_FILENO, &g_data.msh_term);
	g_data.msh_term.c_lflag &= ~(ICANON | ECHO);
	g_data.msh_term.c_cc[VMIN] = 1;
	g_data.msh_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_data.msh_term);
	while (1)
	{
		prompt();
		if (proc_child() == 1)
		{
			ft_putendl_fd(NULL, 1);
			break ;
		}
		ft_putendl_fd(NULL, 1);
		// add_history(g_data.input);
	}
	// free(g_data.input);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_data.org_term);
	return (0);
}
