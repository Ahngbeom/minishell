/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _split_2_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:43:13 by bahn              #+#    #+#             */
/*   Updated: 2022/01/20 21:21:16 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	size_t	count_command(char *input)
{
	size_t	cnt;

	cnt = 0;
	while (*input != '\0')
	{
		if (*input == '\'')
		{
			while (*(++input) != '\"')
			{
				if (*input == '\0')
					break ; // more_input
			}
			++input;
		}
		else if (*input == '\"')
		{
			while (*(++input) != '\"')
			{
				if (*input == '\0')
					break ; // more_input
			}
			++input;
		}
		else if (*input == ';')
		{
			input++;
			if (*input != '\0')
				cnt++;
		}
		else
			++input;
	}
	return (++cnt);
}

static	char	*command_extractor(char *input, int *start_idx)
{
	char	*command;
	
	command = NULL;
	while (input[*start_idx] != '\0')
	{
		if (input[*start_idx] == '\'')
		{
			while (input[++(*start_idx)] != '\"')
			{
				if (input[*start_idx] == '\0')
					break ; // more_input
			}
			++(*start_idx);
		}
		else if (input[*start_idx] == '\"')
		{
			while (*(++input) != '\"')
			{
				if (input[*start_idx] == '\0')
					break ; // more_input
			}
			++(input);
		}
		if (input[*start_idx] == ';')
		{
			command = ft_substr(input, 0, (*start_idx)++);
			return (command);
		}
		else
			++(*start_idx);
	}
	return (ft_strdup(input));
}

static	void	splitter(char *input, size_t count)
{
	char	*copy_input;
	char	*temp;
	size_t	i;
	int		idx;

	command->argv = ft_calloc(sizeof(char *), )
	copy_input = input;
	temp = NULL;
	i = 0;
	while (i < count)
	{
		idx = 0;
		command->argv[i] = command_extractor(copy_input, &idx);
		if (copy_input != NULL && copy_input != input)
			temp = copy_input;
		while (copy_input[idx] == ' ')
			idx++;
		if (copy_input[idx] != '\0')
			copy_input = ft_substr(copy_input, idx, ft_strlen(copy_input));
		if (temp != NULL)
			free(temp);
		i++;
	}
}

void	split_2_command(t_command **commands, char *input)
{
	int		count_cmds;
	int		i;

	printf("[split 2 command]\n");
	count_cmds = count_command(input);
	printf("%d\n", count_cmds);
	// commands = ft_calloc(sizeof(char *), count_cmds + 1);
	// if (commands == NULL)
	// 	exit(EXIT_FAILURE);
	*commands = ft_calloc(sizeof(t_command), 1);
	splitter(*commands, input, count_cmds);
	printf(" [Splitter RESULT] \n");
	i = -1;
	while (commands[++i] != NULL)
	{
		printf("%s\n", commands[i]);
		free(commands[i]);
	}
	free(commands);
	// return (ft_splitter(commands, sptr, c, count_cmds));
}
