/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2021/12/20 21:43:44 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_free(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}

int	minishell(void)
{
	int		rtn;
	pid_t	execve_pid;
	int		status;
	
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	g_data.input = readline(prompt());
	if (g_data.input != NULL)
	{
		if (!ft_strncmp(g_data.input, "\n", ft_strlen(g_data.input)))
			return (0);
		else if (!ft_strncmp(g_data.input, "exit", ft_strlen(g_data.input) + 1))
		{
			ft_putendl_fd("exit", 1);
			return (1);
		}
		rtn = parsing();
		if (rtn == EXEC_PROC)
		{
			execve_pid = fork();
			if (execve_pid < 0)
				exit(EXIT_FAILURE);
			else if (execve_pid == 0)
			{
				// free(g_data.argv);
				g_data.cmd_path = ft_strjoin(BIN_PATH, g_data.argv[0]);
				// env_chararr_converter();
				if (execve(g_data.cmd_path, g_data.argv, g_data.org_env) == -1)
				{
					printf("execve Error: %s\n", strerror(errno));
					exit(EXIT_FAILURE);
				}
			}
			else
			{	
				waitpid(execve_pid, &status, 0);
				add_history(g_data.input);
				// free(g_data.input);
			}
			return (0);
		}
		add_history(g_data.input);
		free(g_data.input);
		split_free(g_data.argv);
		return (0);
	}
	else
	{
		ft_putendl_fd("exit", 1);
		return (1);
	}
}
