/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:45:03 by bahn              #+#    #+#             */
/*   Updated: 2021/12/23 12:58:18 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_countstrs(t_list **list, char *input, char **redirect)
{
	size_t	cnt;
	char	*ptr;
	char	*temp;
	int		i;
	t_command *cmd;
	
	cnt = 0;
	ptr = input;
	while (ptr != NULL && *ptr != '\0')
	{
		cmd = ft_calloc(sizeof(t_command), 1);
		i = -1;
		while (redirect[++i] != NULL)
		{
			temp = ft_strnstr(ptr, redirect[i], ft_strlen(ptr));
			if (temp != NULL)
			{
				cmd->argv = ft_split(ft_substr(ptr, 0, ft_strlen(ptr) - ft_strlen(temp)), ' ');
				cmd->redirect = redirect[i];
				if (list == NULL)
					*list = ft_lstnew(cmd);
				else
					ft_lstadd_back(list, ft_lstnew(cmd));
				cnt++;
				ptr = temp + ft_strlen(redirect[i]);
				while (*ptr != '\0' && !ft_isalpha(*ptr))
					ptr++;
				break ;
			}
		}
		if (redirect[i] == NULL)
		{
			cmd->argv = ft_split(ptr, ' ');
			cmd->redirect = redirect[i];
			if (list == NULL)
				*list = ft_lstnew(cmd);
			else
				ft_lstadd_back(list, ft_lstnew(cmd));
			cnt++;
			break ;
		}
	}
}

void	ft_split_command(t_list **list, char *input, char **redirect)
{
	if (!input)
		return ;
	ft_countstrs(list, input, redirect);
}
