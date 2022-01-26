/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 23:12:35 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 10:41:56 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_stat_converter(char **arg, char *find)
{
	char	*next_tmp;

	next_tmp = NULL;
	if (*(find + 2) != '\0')
		next_tmp = ft_substr(find + 2, 0, ft_strlen(find + 2));
	free(*arg);
	if (next_tmp != NULL)
	{
		*arg = ft_strjoin(g_data.exit_stat, next_tmp);
		free(next_tmp);
	}
	else
		*arg = ft_strdup(g_data.exit_stat);
}

static int	envv_cutter(char **arg, char *find)
{
	int		i;
	char	*temp;

	i = -1;
	while (find[++i] != '\0')
	{
		if (i == 0 && ft_isdigit(find[i]))
		{
			temp = *arg;
			*arg = ft_substr(find + i + 1, 0, ft_strlen(find + i + 1));
			free(temp);
			break ;
		}
		else if (!ft_isalnum(find[i]) && find[i] != '_')
			break ;
	}
	return (i);
}

static void	envv_converter(char **arg, char *find)
{
	char	*next_tmp;
	char	*key;
	int		i;

	next_tmp = NULL;
	i = envv_cutter(arg, find);
	if (i == 0)
		return ;
	if (*(find + i) != '\0')
		next_tmp = ft_substr(find + i, 0, ft_strlen(find + i));
	key = ft_substr(find, 0, i);
	free(*arg);
	*arg = get_envv_value(key);
	free(key);
	if (*arg == NULL)
		*arg = ft_strdup("\0");
	if (next_tmp != NULL)
	{
		*arg = ft_strjoin(*arg, next_tmp);
		free(next_tmp);
	}
	else
		*arg = ft_strdup(*arg);
}

void	envmark_converter(char **arg)
{
	char	*find;
	char	*prev_tmp;
	char	*tmp;

	prev_tmp = NULL;
	find = ft_strchr(*arg, '$');
	if (find == NULL || ft_strlen(*arg) <= 1)
		return ;
	while (find)
	{
		if (find > *arg)
			prev_tmp = ft_substr(*arg, 0, find - *arg);
		if (*(find + 1) == '?')
			exit_stat_converter(arg, find);
		else
			envv_converter(arg, find + 1);
		if (prev_tmp != NULL)
		{
			tmp = *arg;
			*arg = ft_strjoin(prev_tmp, *arg);
			free(tmp);
			free(prev_tmp);
		}
		find = ft_strchr(*arg, '$');
	}
}
