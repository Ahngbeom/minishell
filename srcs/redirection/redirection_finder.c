/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_finder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:06:05 by bahn              #+#    #+#             */
/*   Updated: 2022/01/08 01:31:12 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_finder(char **input, char *redirection[], t_command *cmd)
{
	char	*find_ptr;
	char	*forefront;
	char	**new_argv;
	char	*tmp;
	char	**ttmp;
	int		i;
	int		j;

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
	if (forefront == NULL)
		return (0);
	else
	{
		// *input = forefront + 1;
		if (ft_strlen(*input) == ft_strlen(cmd->redirect))
		{
			ttmp = cmd->argv;
			new_argv = ft_calloc(sizeof(char *), argv_counter(cmd->argv));
			i = -1;
			j = i;
			while (cmd->argv[++i] != NULL)
			{
				if (!ft_strncmp(cmd->argv[i], cmd->redirect, ft_strlen(cmd->argv[i]) + 1))
					i += 1;
				new_argv[++j] = ft_strdup(cmd->argv[i]);
			}
			cmd->argv = new_argv;
			split_free(ttmp);
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
			if (redirection_finder(&cmd_ptr->argv[i], g_data.arr_redirect, cmd_ptr))
			{
				break ;
			}
		}
		lst_ptr = lst_ptr->next;
	}
}
