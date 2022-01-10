/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 23:12:35 by bahn              #+#    #+#             */
/*   Updated: 2022/01/11 02:15:18 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	remaining_strjoin(char *str, char **result)
{
	char	*temp;

	if (*str != '\0')
	{
		if (*result != NULL)
		{
			temp = *result;
			*result = ft_strjoin(*result, str);
			free(temp);
		}
		else
			*result = ft_strdup(str);
	}
}

static	void	temp_store(char **temp, char *str, size_t len)
{
	*temp = ft_substr(str, 0, len);
}

static	char	*converter_by_key(char *ptr)
{
	int		i;
	char	*ext_key;
	char	*result;

	i = 1;
	while (ft_isalpha(ptr[i]) || ptr[i] == '_')
		i++;
	ext_key = ft_substr(ptr, 1, i - 1);
	if (get_envv_value(ext_key) != NULL)
		result = ft_strdup(get_envv_value(ext_key));
	else
		result = ft_strdup("");
	remaining_strjoin(ptr + i, &result);
	return (result);
}

// Try echo $HOME@@@@ on bash and minishell
// Try echo $HOME\ $HOME\\ on bash and minishell
char	*envv_converter(char *arg)
{
	char	*envvmark;
	char	*temp;
	char	*result;

	temp = NULL;
	result = arg;
	envvmark = ft_strchr(result, '$');
	while (envvmark)
	{
		if (envvmark != result)
			temp_store(&temp, result, envvmark - result);
		if (*(envvmark + 1) == '?')
			result = ft_strjoin(g_data.exit_stat, envvmark + 2);
		else
			result = converter_by_key(envvmark);
		if (temp != NULL)
			result = ft_strjoin_with_free(temp, result);
		envvmark = ft_strchr(result, '$');
	}
	if (result != arg)
		free(arg);
	return (result);
}
