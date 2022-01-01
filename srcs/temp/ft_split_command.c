/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:45:03 by bahn              #+#    #+#             */
/*   Updated: 2021/12/30 18:08:01 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// https://ahngbeom-bahn.notion.site/1487214afdfb44d4aa01ad6e0391da2e

static	char	*redirection_finder(char *dest, char **src, char **find_redirection)
{
	char	*find_ptr;	// 리다이렉션 탐색 결과를 저장할 변수
	char	*forefront;	// 가장 전방에 있는 리다이렉션
	int		i;

	forefront = NULL;
	find_ptr = NULL;
	i = -1;
	while (src[++i] != NULL)
	{
		find_ptr = ft_strnstr(dest, src[i], ft_strlen(dest));
		// 만약 현재 find_ptr이 이전에 찾은 find_ptr(forefront)보다 전방에 위치한다면
		if (find_ptr != NULL && (forefront == NULL || forefront > find_ptr))
		{
			forefront = find_ptr;
			*find_redirection = src[i];
		}
	}
	return (forefront);
}

void	ft_split_command(t_list **list, char *input, char **redirect)
{
	char		*ptr;
	t_command	*cmd;
	char		*temp;

	ptr = input;
	while (ptr != NULL && *ptr != '\0')
	{
		cmd = ft_calloc(sizeof(t_command), 1);
		if (list == NULL)
			*list = ft_lstnew(cmd);
		else
			ft_lstadd_back(list, ft_lstnew(cmd));
		cmd->bulit_in_flag = 0;
		temp = redirection_finder(ptr, redirect, &cmd->redirect);
		if (temp != NULL)
		{
			cmd->argv = ft_split(ft_substr(ptr, 0, ft_strlen(ptr) - ft_strlen(temp)), ' ');
			ptr = ft_strtrim(temp + ft_strlen(cmd->redirect) + 1, " ");
		}
		else
		{
			cmd->argv = ft_split(ptr, ' ');
			break ;
		}
	}
	if (ptr == input)
		free(input);
	else
		free(ptr);
}
