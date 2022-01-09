/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 13:30:19 by bahn              #+#    #+#             */
/*   Updated: 2022/01/09 01:16:48 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_split(t_list **list, char *input)
{
	t_command	*command;
	int			redir_idx;
	char		*temp;

	while (*input != '\0')
	{
		if (*input == ' ')
			input++;
		else
		{
			command = ft_calloc(sizeof(t_command), 1);
			redir_idx = redirection_finder(g_data.arr_redirect, input, &command->redirect);
			if (redir_idx >= 0)
			{
				temp = ft_substr(input, 0, redir_idx);
				command->argv = ft_calloc(sizeof(char *), arg_finder(NULL, temp) + 1);
				arg_finder(command, temp);
				free(temp);
				if (*list == NULL)
					*list = ft_lstnew(command);
				else
					ft_lstadd_back(list, ft_lstnew(command));
				input += redir_idx + 1;
			}
			else
			{
				command->argv = ft_calloc(sizeof(char *), arg_finder(NULL, input) + 1);
				arg_finder(command, input);
				if (*list == NULL)
					*list = ft_lstnew(command);
				else
					ft_lstadd_back(list, ft_lstnew(command));
				break ;
			}
		}
	}
}
