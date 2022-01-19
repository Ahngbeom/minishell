/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:43:13 by bahn              #+#    #+#             */
/*   Updated: 2022/01/20 02:38:01 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	size_t	count_command(char *input)
{
	size_t	cnt;

	cnt = 0;
	while (*input != '\0')
	{
		if (*input != ';')
		{
			cnt++;
			while (*(++input) != ';')
			{
				if (*input == '\0')
					break ;
			}
		}
		else
			++input;
	}
	return (cnt);
}

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

void	split_2_command(t_list **list, char *input)
{
	// char	**commands;
	int		count_cmds;

	printf("[split 2 command]\n");
	(void)list;
	count_cmds = count_command(input);
	printf("%d\n", count_cmds);
	// commands = (char **)malloc(sizeof(char *) * (count_cmds + 1));
	// if (commands == NULL)
	// 	return (NULL);
	// return (ft_splitter(commands, sptr, c, count_cmds));
}
