/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:46:46 by bahn              #+#    #+#             */
/*   Updated: 2021/12/21 15:21:45 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_flag_checker(char *argv)
{
	int		j;
	
	if (argv[0] == '-')
	{
		j = 1;
		while (argv[j] == 'n' && argv[j] != '\0')
			j++;
		if (argv[j] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

static	char	*remove_enclosed_quotes(char *argv)
{
	char	*result;
	
	// Redirection
	result = ft_strtrim(argv, "\"\'");
	free(argv);
	return (result);
}

static	int	envmark_checker(char *env, int dest_idx)
{
	if (*env == '$')
	{
		// Try echo $HOME@@@@ on bash and minishell
		g_data.argv[dest_idx] = ft_substr(env, 1, ft_strlen(env) - 1);
		free(env);
		ft_putstr_fd(env_getvalue(g_data.argv[dest_idx]), 1);
		return (1);
	}
	return (0);
}

static	int		backslash_checker(int argv_idx, int *ch_idx)
{
	if (g_data.argv[argv_idx][*ch_idx] == '\\')
	{
		if (g_data.argv[argv_idx][*ch_idx + 1] == '\\' || \
				g_data.argv[argv_idx][*ch_idx + 1] == '\'' || \
					g_data.argv[argv_idx][*ch_idx + 1] == '\"')
		{
			*ch_idx += 1;
			return (1);
		}
		return (0);
	}
	else if (g_data.argv[argv_idx][*ch_idx] == '\\' || \
				g_data.argv[argv_idx][*ch_idx] == '\'' || \
					g_data.argv[argv_idx][*ch_idx] == '\"')
		return (0);
	else
		return (1);
}

int	minishell_echo(void)
{
	int		i;
	int		j;
	
	i = 0;
	while (g_data.argv[++i] != NULL)
	{
		// printf("(%s)", g_data.argv[i]);
		// printf("[%d]", find_n(g_data.argv[i]));
		if (i == 1 && n_flag_checker(g_data.argv[i]))
			continue ;
		else
			g_data.argv[i] = remove_enclosed_quotes(g_data.argv[i]);
		j = -1;
		while (g_data.argv[i][++j] != '\0' && g_data.argv[i][j] != ';')
		{
			if (envmark_checker(g_data.argv[i], i))
				break ;
			//else if (!ft_isalnum(g_data.argv[i][j]))
			//	continue ;
			else if (backslash_checker(i, &j))
				ft_putchar_fd(g_data.argv[i][j], 1);
			else
				continue;
		}
		if (g_data.argv[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (g_data.argv[1] == NULL || !(n_flag_checker(g_data.argv[1])))
		ft_putchar_fd('\n', 1);
	return (SELF_PROC);
}
