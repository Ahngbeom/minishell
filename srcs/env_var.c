/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:08:21 by bahn              #+#    #+#             */
/*   Updated: 2021/12/14 14:38:19 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envvar_checker(void)
{
	char	*temp;
	int		i;
	int		j;
	
	if (argv_counter(g_data.argv) == 2 && g_data.argv[1][0] == '$')
	{
		temp = ft_strtrim(g_data.argv[1], "$\n");
		ft_split(g_data.argv[1], LF);
		if (getenv(temp))
			printf("%s\n", getenv(temp));
		else
		{
			printf("\n");
		}
		free(temp);
		return (-1);
	}
	else if (argv_counter(g_data.argv) == 3 && g_data.argv[2][0] == '$')
	{
		temp = ft_strtrim(g_data.argv[2], "$\n");
		if (getenv(temp))
			printf("%s\n", getenv(temp));
		else
			printf("\n");
		free(temp);
		return (-1);
	}
	else
	{
		i = 0;
		while (g_data.argv[++i] != NULL)
		{
			j = -1;
			while (g_data.argv[i][++j] != '\0')
			{
				printf("-n\n");
				if (g_data.argv[i][j] == '\\' && ft_isprint(g_data.argv[i][j + 1]))
					ft_putchar_fd(g_data.argv[i][++j], 1);
				else
					ft_putchar_fd(g_data.argv[i][j], 1);
			}
			if (g_data.argv[i + 1] != NULL)
				ft_putchar_fd(' ', 1);
		}
		if (g_data.argv[1] != NULL && ft_strncmp(g_data.argv[1], "-n", ft_strlen("-n")))
			ft_putchar_fd('\n', 1);
		return (-1);
	}
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
		env_dupl[i] = ft_strdup(env[i]);
	env_dupl[i] = NULL;
	return (env_dupl);
}

void	free_env(char *env[])
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		free(env[i]);
	free(env);
}
