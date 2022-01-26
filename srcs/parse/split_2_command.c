/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:43:13 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 20:15:24 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	determine_enclosed_quotes(char *start_quotes, char *type_ptr, \
										t_command *command)
{
	char	quotes;
	char	*end_quotes;

	if (start_quotes == NULL && type_ptr)
	{
		set_type(command, &type_ptr);
		return (1);
	}
	quotes = *start_quotes;
	if (type_ptr && start_quotes < type_ptr)
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

static int	enclosed_quotes_checker(char *sentence, char *type_ptr, \
									t_command *command)
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
	*sentence = ft_strtrim_with_free(*sentence, " ");
	command->argv = quotes_split(*sentence, ' ');
	free(*sentence);
}

int	split_2_command(t_list **list, char *input)
{
	t_command	*command;
	char		*splitted;
	int			extractor;
	char		*processed;

	processed = ft_strdup_with_free(input);
	splitted = NULL;
	extractor = command_extractor(&processed, &splitted);
	while (extractor > 0)
	{
		add_command_to_list(list, &command);
		arg_extractor(command, &splitted);
		remove_quotes(command);
		extractor = command_extractor(&processed, &splitted);
	}
	if (processed != NULL)
		free(processed);
	if (extractor == -1)
	{
		ft_lstclear(list, command_free);
		return (extractor);
	}
	return (0);
}
