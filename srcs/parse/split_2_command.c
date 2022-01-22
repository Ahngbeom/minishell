/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:43:13 by bahn              #+#    #+#             */
/*   Updated: 2022/01/22 18:11:43 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	char	*ft_findstr(char *s, char c)
// {
// 	while (*s != '\0')
// 	{
// 		if (*s == c)
// 			s++;
// 		else
// 			return (s);
// 	}
// 	return (0);
// }

// static	size_t	ft_strclen(char *s, char c)
// {
// 	size_t	length;
// 	char	*ptr;

// 	length = 0;
// 	ptr = s;
// 	while (*ptr != '\0' && *ptr != c)
// 	{
// 		length++;
// 		ptr++;
// 	}
// 	return (length);
// }

// static	char	**ft_splitter(char **pptr, char *str_ptr, char c, size_t str_cnt)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < str_cnt)
// 	{
// 		pptr[i] = (char *)malloc(ft_strclen(ft_findstr(str_ptr, c), c) + 1);
// 		if (pptr[i] == NULL)
// 		{
// 			while (pptr[i] != NULL)
// 				free(pptr[i++]);
// 			free(pptr);
// 			return (pptr);
// 		}
// 		ft_strlcpy(pptr[i], ft_findstr(str_ptr, c), ft_strclen(ft_findstr(str_ptr, c), c) + 1);
// 		str_ptr = ft_findstr(ft_findstr(str_ptr, c) + ft_strclen(ft_findstr(str_ptr, c), c), c);
// 		i++;
// 	}
// 	pptr[i] = NULL;
// 	return (pptr);
// }

static	size_t	command_finder(char **input, char **splitted)
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
		else if (type_finder(ptr))
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

static void	arg_extractor(t_command *command, char *sentence)
{
	char	*type;

	type = type_finder(sentence);
	if (type)
	{
		sentence = ft_substr(sentence, 0, type - sentence);
	}
	command->argv = ft_split(sentence, " ");
}

void	split_2_command(t_list **list, char *input)
{
	t_command	*command;
	char		*splitted;

	splitted = NULL;
	while (command_finder(&input, &splitted) > 0)
	{
		command = ft_calloc(sizeof(t_command), 1);
		arg_extractor(command, splitted);
		set_type(command, splitted);
		if (*list == NULL)
			*list = ft_lstnew(command);
		else
			ft_lstadd_back(list, ft_lstnew(command));
		printf("splitted : %s\n", splitted);
		// printf("argv[0] : %s\n", command->argv[0]);
		printf("type : %s\n", command->type);
		// splitted -> cmd->argv;
		free(splitted);
		splitted = NULL;
		printf("input : %s\n", input);

	}
	if (input != NULL)
		free(input);
	// commands = (char **)malloc(sizeof(char *) * (count_cmds + 1));
	// if (commands == NULL)
	// 	return (NULL);
	// return (ft_splitter(commands, sptr, c, count_cmds));
}
