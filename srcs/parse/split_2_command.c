/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:43:13 by bahn              #+#    #+#             */
/*   Updated: 2022/01/23 04:12:41 by bahn             ###   ########.fr       */
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
		if (quote_finder(&ptr, &length))
			continue ;
		if (type_finder(ptr))
		{
			length++;
			ptr++;
			break ;
		}
		length++;
		ptr++;
	}
	if (length > 0)
	{
		*splitted = ft_substr(*input, 0, length);
		printf("?input : %s\n", *input);
		temp = *input;
		*input = ft_substr(*input, length, ft_strlen(*input));
		free(temp);
		printf("?input : %s\n", *input);
		// temp = *input;
		// *input = ft_strtrim(*input, " ");
		// free(temp);
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

static int	enclosed_quotes_checker(char *sentence, char *type_ptr)
{
	char	*ptr;
	int		length;

	ptr = sentence;
	length = 0;
	quote_finder(&ptr, &length);
	if (ptr <= type_ptr)
		return (1);
	else
		return (0);
}

static void	arg_extractor(t_command *command, char **sentence)
{
	char	*type;
	char	*temp;

	type = type_finder(*sentence);
	if (type && enclosed_quotes_checker(*sentence, type))
	{
		set_type(command, sentence);
		temp = *sentence;
		*sentence = ft_substr(*sentence, 0, type - *sentence);
		free(temp);
	}
	// remove_quotes(&sentence);
	temp = *sentence;
	*sentence = ft_strtrim(*sentence, " ");
	free(temp);
	command->argv = split_without_quotes(*sentence, ' ');
}

void	split_2_command(t_list **list, char *input)
{
	t_command	*command;
	char		*splitted;
	int			i;

	splitted = NULL;
	while (command_finder(&input, &splitted) > 0)
	{
		printf("splitted : [%s]\n\n", splitted);
		command = ft_calloc(sizeof(t_command), 1);
		set_type(command, &splitted);
		arg_extractor(command, &splitted);
		if (*list == NULL)
			*list = ft_lstnew(command);
		else
			ft_lstadd_back(list, ft_lstnew(command));
		i = -1;
		while (command->argv[++i] != NULL)
		{
			printf("argv[%d] : [%s]\n", i, command->argv[i]);
		}
		printf("argv[%d] : %s\n", i, command->argv[i]);
		printf("type : %s\n", command->type);
		free(splitted);
		splitted = NULL;
		printf("input : [%s]\n\n", input);

	}
	if (input != NULL)
		free(input);
	// commands = (char **)malloc(sizeof(char *) * (count_cmds + 1));
	// if (commands == NULL)
	// 	return (NULL);
	// return (ft_splitter(commands, sptr, c, count_cmds));
}
