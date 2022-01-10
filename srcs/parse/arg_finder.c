/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 01:13:30 by bahn              #+#    #+#             */
/*   Updated: 2022/01/10 15:31:06 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	move_pointer(char **ptr, char quotes)
{
	if (quotes != '\"' && quotes != '\'')
		quotes = ' ';
	while (*(++(*ptr)) != quotes)
	{
		if (**ptr == '\0')
			break ;
	}
	++(*ptr);
}

static	char	*arg_compose(char *arg, char **input)
{
	char	*temp;
	char	*temp2;

	if (**input != ' ' && **input != '\0')
	{
		if (**input == '\"' || **input == '\'')
			temp = ft_substr(*input, 1, ft_strchr(*input + 1, **input) - *input - 1);
		else
			temp = ft_substr(*input, 0, ft_strchr(*input + 1, ' ') - *input);
		move_pointer(input, **input);
		temp2 = arg;
		arg = ft_strjoin(arg, temp);
		free(temp2);
		free(temp);
	}
	return (arg);
}

size_t	arg_finder(t_command *cmd, char *input)
{
	size_t	cnt;
	int		i;

	i = -1;
	cnt = 0;
	while (input != NULL && *input != '\0')
	{
		if (*input == '\"' || *input == '\'')
		{
			cnt++;
			if (cmd != NULL)
			{
				cmd->argv[++i] = ft_substr(input + 1, 0, ft_strchr(input + 1, *input) - (input + 1));
				if (*input == '\"')
					cmd->argv[i] = envv_converter(cmd->argv[i]);
			}
			move_pointer(&input, *input);
			if (cmd != NULL)
				cmd->argv[i] = arg_compose(cmd->argv[i], &input);
		}
		else if (*input != ' ')
		{
			cnt++;
			if (cmd != NULL)
			{
				if (ft_strchr(input, ' ') != NULL)
					cmd->argv[++i] = ft_substr(input, 0, ft_strchr(input, ' ') - input);
				else
					cmd->argv[++i] = ft_substr(input, 0, ft_strlen(input));
				cmd->argv[i] = envv_converter(cmd->argv[i]);
				backslash_converter(&cmd->argv[i]);
			}
			while (*(++input) != ' ')
			{
				if (*input == '\0')
					break ;
			}
		}
		else
			input++;
	}
	return (cnt);
}
