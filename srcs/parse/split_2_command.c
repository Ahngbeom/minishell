/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:43:13 by bahn              #+#    #+#             */
/*   Updated: 2022/01/20 21:32:14 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	size_t	count_command(char *input)
// {
// 	size_t	cnt;

// 	cnt = 0;
// 	while (*input != '\0')
// 	{
// 		if (*input == '\'')
// 		{
// 			while (*(++input) != '\"')
// 			{
// 				if (*input == '\0')
// 					break ; // more_input
// 			}
// 			++input;
// 		}
// 		else if (*input == '\"')
// 		{
// 			while (*(++input) != '\"')
// 			{
// 				if (*input == '\0')
// 					break ; // more_input
// 			}
// 			++input;
// 		}
// 		else if (*input == ';')
// 		{
// 			input++;
// 			if (*input != '\0')
// 				cnt++;
// 		}
// 		else
// 			++input;
// 	}
// 	return (++cnt);
// }

// static	char	*command_extractor(char *input, int *start_idx)
// {
// 	char	*command;
	
// 	command = NULL;
// 	while (input[*start_idx] != '\0')
// 	{
// 		if (input[*start_idx] == '\'')
// 		{
// 			while (input[++(*start_idx)] != '\"')
// 			{
// 				if (input[*start_idx] == '\0')
// 					break ; // more_input
// 			}
// 			++(*start_idx);
// 		}
// 		else if (input[*start_idx] == '\"')
// 		{
// 			while (*(++input) != '\"')
// 			{
// 				if (input[*start_idx] == '\0')
// 					break ; // more_input
// 			}
// 			++(input);
// 		}
// 		if (input[*start_idx] == ';')
// 		{
// 			command = ft_substr(input, 0, (*start_idx)++);
// 			return (command);
// 		}
// 		else
// 			++(*start_idx);
// 	}
// 	return (ft_strdup(input));
// }

// static	void	splitter(t_command *command, char *input, size_t count)
// {
// 	char	*copy_input;
// 	char	*temp;
// 	size_t	i;
// 	int		idx;

// 	copy_input = input;
// 	temp = NULL;
// 	i = 0;
// 	while (i < count)
// 	{
// 		idx = 0;
// 		command->argv[i] = command_extractor(copy_input, &idx);
// 		if (copy_input != NULL && copy_input != input)
// 			temp = copy_input;
// 		while (copy_input[idx] == ' ')
// 			idx++;
// 		if (copy_input[idx] != '\0')
// 			copy_input = ft_substr(copy_input, idx, ft_strlen(copy_input));
// 		if (temp != NULL)
// 			free(temp);
// 		i++;
// 	}
// }

void	split_2_command(t_list **commands, char *input)
{
	t_command	*cmd;

	// while ()
	// {
		cmd = ft_calloc(sizeof(t_command), 1);
		if (*commands == NULL)
			*commands = ft_lstnew(cmd);
		else
			ft_lstadd_back(commands, ft_lstnew(cmd));
		cmd->argv = ft_calloc(sizeof(char *), 2);
		cmd->argv[0] = ft_strdup(input);
	// }
	// splitter(*commands, input, count_cmds);
}
