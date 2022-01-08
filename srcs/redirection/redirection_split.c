/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 13:30:19 by bahn              #+#    #+#             */
/*   Updated: 2022/01/08 23:53:01 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quotes_chekcer(char *input, char **r_addr, char *redirection)
{
	char	*ptr;

	ptr = input;
	*r_addr = ft_strnstr(ptr, redirection, ft_strlen(input));
	while (*r_addr)
	{
		if (ft_strchr(ptr, '\'') != NULL && \
			ft_strchr(ptr, '\'') < *r_addr && \
			ft_strchr(ft_strchr(ptr, '\'') + 1, '\'') > *r_addr)
		{
			ptr = ft_strchr(ft_strchr(ptr, '\'') + 1, '\'') + 1;
			*r_addr = ft_strnstr(ptr, redirection, ft_strlen(input));
		}
		else if (ft_strchr(ptr, '\"') != NULL && \
			ft_strchr(ptr, '\"') < *r_addr && \
			ft_strchr(ft_strchr(ptr, '\"') + 1, '\"') > *r_addr)
		{
			ptr = ft_strchr(ft_strchr(ptr, '\"') + 1, '\"') + 1;
			*r_addr = ft_strnstr(ptr, redirection, ft_strlen(input));
		}
		else
			break ;
	}
}

int	redirection_finder2(char *redirection[], char *input, char **save)
{
	char	*find_ptr;
	char	*forefront;
	int		i;

	forefront = NULL;
	find_ptr = NULL;
	i = -1;
	while (redirection[++i] != NULL)
	{
		quotes_chekcer(input, &find_ptr, redirection[i]);
		if (find_ptr != NULL && (forefront == NULL || forefront > find_ptr))
		{
			forefront = find_ptr;
			if (save != NULL)
				*save = redirection[i];
		}
	}
	if (forefront != NULL)
		return (forefront - input);
	else
		return (-1);
}

void	redirection_split(t_list **list, char *input)
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
			redir_idx = redirection_finder2(g_data.arr_redirect, input, &command->redirect);
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
