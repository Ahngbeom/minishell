/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:01:22 by bahn              #+#    #+#             */
/*   Updated: 2022/01/02 14:45:13 by bahn             ###   ########.fr       */
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
	g_data.arr_redirect[6] = NULL;
}

static	void	set_envvpath(void)
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
	int			i;
	char		*temp;
	char		*input;

	(void)argv;
	g_data.org_envv = env;
	g_data.envv = set_lstenv(env);
	set_envvpath();
	// if (chdir(getenv("HOME")) == -1)
		// exit(errno);
	// free(envv_get("PWD")->value);
	// envv_get("PWD")->value = getcwd(NULL, 0);
	g_data.commands = NULL;
	set_redirection();
	g_data.status = 0;
	g_data.pipe = malloc(sizeof(int) * 2);

	//	ioctl 함수를 통해 EscapeSequence 해결?
	// if (tcgetattr(STDIN_FILENO, &g_data.termios))
		// exit(EXIT_FAILURE);
	// g_data.termios.c_lflag = ICANON | ~ECHO;
	// g_data.termios.c_cc[VMIN] = 1;
	// g_data.termios.c_cc[VTIME] = 0;
	// if (tcsetattr(STDIN_FILENO, TCSANOW, &g_data.termios))
		// exit(EXIT_FAILURE);
	
	if (argc > 1 && !ft_strncmp(argv[1], "-c", ft_strlen("-c") + 1))
	{
		if (argc > 2)
		{
			input = NULL;
			i = 1;
			while (++i < argc)
			{
				if (i + 1 >= argc)
				{
					if (input == NULL)
						input = ft_strdup(argv[i]);
					else
					{
						temp = ft_strjoin(input, " ");
						input = ft_strjoin(temp, argv[i]);
						free(temp);
					}
				}
				else
				{
					temp = ft_strjoin(argv[i], " ");
					input = ft_strjoin(temp, argv[++i]);
					free(temp);
				}
			}
			minishell(input);
		}
		minishell_finalize();
		exit(g_data.status);
	}
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
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		if (minishell(readline(prompt())) < 0)
			break ;
	}
	minishell_finalize();
	
	// system("leaks minishell > leaks_result && cat leaks_result && rm -rf leaks_result");
	
	return (g_data.status);
}
