/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:43:13 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 01:25:01 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	command_finder(char **input, char **splitted)
{
	char	*ptr;
	int		length;
	char	*temp;

	ptr = *input;
	length = 0;
	while (*ptr != '\0')
	{
		if (quote_finder(&ptr, &length, input))
			continue ;
		if (type_finder(ptr, &length, input))
			break ;
		length++;
		ptr++;
	}
	if (length > 0)
	{
		*splitted = ft_substr(*input, 0, length);
		temp = *input;
		*input = ft_substr(*input, length, ft_strlen(*input));
		free(temp);
		if (ft_strlen(*splitted) != length)
		{
			temp = *splitted;
			*splitted = ft_substr(*input, 0, length);
			free(temp);
		}
		return (1);
	}
	return (0);
}

static int	determine_enclosed_quotes(char *start_quotes, char *type_ptr, t_command *command)
{
	char	quotes;
	char	*end_quotes;

	if (start_quotes == NULL)
	{
		set_type(command, &type_ptr);
		return (1);
	}
	quotes = *start_quotes;
	if (start_quotes < type_ptr)
	{
		end_quotes = ft_strchr(start_quotes + 1, quotes);
		if (end_quotes && end_quotes < type_ptr)
		{
			set_type(command, &type_ptr);
			return (1);
		}
	}
	return (0);
}

static int	enclosed_quotes_checker(char *sentence, char *type_ptr, t_command *command)
{
	char	*sgle;
	char	*dble;

	sgle = ft_strchr(sentence, '\'');
	dble = ft_strchr(sentence, '\"');
	if (sgle && dble)
		return (determine_enclosed_quotes(sgle, type_ptr, command) && \
				determine_enclosed_quotes(dble, type_ptr, command));
	else if (sgle)
		return (determine_enclosed_quotes(sgle, type_ptr, command));
	else if (dble)
		return (determine_enclosed_quotes(dble, type_ptr, command));
	else
		return (determine_enclosed_quotes(NULL, type_ptr, command));
}

static void	arg_extractor(t_command *command, char **sentence)
{
	char	*type;
	char	*temp;

	type = type_finder(*sentence, NULL, NULL);
	if (type && enclosed_quotes_checker(*sentence, type, command))
	{
		temp = *sentence;
		*sentence = ft_substr(*sentence, 0, type - *sentence);
		free(temp);
	}
	temp = *sentence;
	*sentence = ft_strtrim(*sentence, " ");
	free(temp);
	command->argv = split_without_quotes(*sentence, ' ');
}

void	split_2_command(t_list **list, char *input)
{
	t_command	*command;
	char		*splitted;

	splitted = NULL;
	while (command_finder(&input, &splitted) > 0)
	{
		command = ft_calloc(sizeof(t_command), 1);
		arg_extractor(command, &splitted);
		remove_quotes(command);
		if (*list == NULL)
			*list = ft_lstnew(command);
		else
			ft_lstadd_back(list, ft_lstnew(command));
		free(splitted);
		splitted = NULL;
	}
	if (input != NULL)
		free(input);
}
