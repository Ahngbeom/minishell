/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 21:22:04 by bahn              #+#    #+#             */
/*   Updated: 2022/01/02 00:50:39 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*move_pointer(char *ptr, char quotes)
{
	if (quotes != '\"' && quotes != '\'')
		quotes = ' ';
	while (*(++ptr) != quotes)
	{
		if (*ptr == '\0')
			break ;
	}
	return (++ptr);
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
		*input = move_pointer(*input, **input);
		temp2 = arg;
		arg = ft_strjoin(arg, temp);
		free(temp2);
		free(temp);
	}
	return (arg);
}

static	size_t	arg_finder(t_command *cmd, char *input)
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
				cmd->argv[++i] = ft_substr(input + 1, 0, ft_strchr(input + 1, *input) - (input + 1));
			input = move_pointer(input, *input);
			if (cmd != NULL)
				cmd->argv[i] = arg_compose(cmd->argv[i], &input);
		}
		else if (*input != ' ')
		{
			// if (*(input + 1) == '\"' || *(input + 1) == '\'')
			// 	continue ;
			cnt++;
			if (cmd != NULL)
			{
				if (ft_strchr(input, ' ') != NULL)
					cmd->argv[++i] = ft_substr(input, 0, ft_strchr(input, ' ') - input);
				else
					cmd->argv[++i] = ft_substr(input, 0, ft_strlen(input));
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

void	input_split(t_list **list, char *input)
{
	t_command	*command;
	char		**split_cmd;

	
	command = ft_calloc(sizeof(t_command), 1);
	if (*list == NULL)
		*list = ft_lstnew(command);
	else
		ft_lstadd_back(list, ft_lstnew(command));
	command->argv = ft_calloc(sizeof(char *), arg_finder(NULL, input) + 1);
	arg_finder(command, input);
	free(input);
}
