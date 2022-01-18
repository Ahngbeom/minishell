/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 13:30:19 by bahn              #+#    #+#             */
/*   Updated: 2022/01/19 01:02:36 by bahn             ###   ########.fr       */
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
			/*
			==16505== 40 bytes in 1 blocks are definitely lost in loss record 14 of 64
			==16505==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
			==16505==    by 0x10E129: ft_calloc (ft_calloc.c:20)
			==16505==    by 0x10BC49: input_split (input_split.c:28)
			==16505==    by 0x1097E2: main (main.c:86)
			*/
			command = ft_calloc(sizeof(t_command), 1);
			redir_idx = redirection_finder(g_data.arr_redirect, input, &command->type);
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
				input += redir_idx + ft_strlen(command->type);
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
