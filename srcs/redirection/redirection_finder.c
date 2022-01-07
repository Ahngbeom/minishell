/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_finder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:06:05 by bahn              #+#    #+#             */
/*   Updated: 2022/01/07 21:23:17 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_finder(char **input, char *redirection[], t_command *cmd)
{
	char	*find_ptr;
	char	*forefront;
	char	*tmp;
	int		i;

	forefront = NULL;
	find_ptr = NULL;
	i = -1;
	while (redirection[++i] != NULL)
	{
		find_ptr = ft_strnstr(*input, redirection[i], ft_strlen(*input));
		if (find_ptr != NULL && (forefront == NULL || forefront > find_ptr))
		{
			forefront = find_ptr;
			if (cmd != NULL)
				cmd->redirect = redirection[i];
		}
	}
	if (find_ptr == NULL)
		return (0);
	else
	{
		// *input = forefront + 1;
		if (cmd != NULL)
		{
			if (ft_strlen(*input) == ft_strlen(cmd->redirect))
			{
				
			}
			else
			{
				tmp = *input;
				if (forefront != *input)
					*input = ft_substr(*input, 0, forefront - *input);
				else
					*input = ft_substr(*input, ft_strlen(cmd->redirect), ft_strlen(*input));
				free(tmp);
			}
		}
		printf("move pointer by redirection : %s\n", *input);
		return (1);
	}
}

void	refact_by_redirection(t_list **list)
{
	t_list		*lst_ptr;
	t_command	*cmd_ptr;
	int			i;

	lst_ptr = *list;
	while (lst_ptr != NULL)
	{
		cmd_ptr = lst_ptr->content;
		i = -1;
		while (cmd_ptr->argv[++i] != NULL)
		{
			if (redirection_finder(&cmd->argv[i], g_data.arr_redirect, cmd_ptr))
			{
				break ;
			}
		}
		lst_ptr = lst_ptr->next;
	}
}
