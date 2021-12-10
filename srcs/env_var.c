/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:08:21 by bahn              #+#    #+#             */
/*   Updated: 2021/12/10 19:12:07 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
