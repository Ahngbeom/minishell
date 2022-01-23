/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_without_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 21:22:04 by bahn              #+#    #+#             */
/*   Updated: 2022/01/23 04:46:01 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	size_t	ft_countstrs(char *s, char c)
// {
// 	size_t	cnt;

// 	cnt = 0;
// 	while (*s != '\0')
// 	{
// 		printf("???????????????????????????\n");
// 		if (*s == '\'')
// 		{
// 			cnt++;
// 			while (*(++s) != '\'')
// 				continue ;
// 		}
// 		else if (*s == '\"')
// 		{
// 			cnt++;
// 			while (*(++s) != '\"')
// 				continue ;
// 		}
// 		else if (*s != c)
// 		{
// 			cnt++;
// 			while (*(++s) != '\0' && *s != c && *s != '\'' && *s != '\"')
// 				continue ;
// 			if (*s == '\'')
// 			{
// 				while (*(++s) != '\'')
// 					continue ;
// 			}
// 			else if (*s == '\"')
// 			{
// 				while (*(++s) != '\"')
// 					continue ;
// 			}
// 		}
// 		else
// 			s++;
// 	}
// 	return (cnt);
// }

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
		// printf("ptr[%d] : %s(flag : %d)\n", i, ptr + i, quotes_flag);
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
