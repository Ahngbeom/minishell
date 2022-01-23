/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_without_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 21:22:04 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 00:00:38 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_without_quotes(char *s, char c)
{
	t_list	*list;
	t_list	*lst_ptr;
	t_list	*temp;
	char	**result;
	char	*ptr;
	int		i;
	char	*splitted;
	int		quotes_flag;

	list = NULL;
	quotes_flag = 0;
	ptr = s;
	i = -1;
	while (ptr[++i] != '\0')
	{
		if (ptr[i] == '\'' || ptr[i] == '\"')
		{
			if (quotes_flag)
				quotes_flag = 0;
			else
				quotes_flag = 1;
		}
		else if (ptr[i] == c && !quotes_flag)
		{
			splitted = ft_substr(ptr, 0, i);
			ft_lstadd_back(&list, ft_lstnew(splitted));
			ptr += (++i);
			i = -1;
		}
	}
	splitted = ft_substr(ptr, 0, i);
	ft_lstadd_back(&list, ft_lstnew(splitted));
	result = ft_calloc(sizeof(char *), ft_lstsize(list) + 1);
	lst_ptr = list;
	i = 0;
	while (lst_ptr != NULL)
	{
		temp = lst_ptr->next;
		result[i++] = (char *)lst_ptr->content;
		free(lst_ptr);
		lst_ptr = temp;
	}
	return (result);
}
