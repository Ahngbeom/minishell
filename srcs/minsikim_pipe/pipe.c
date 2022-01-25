/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2022/01/25 17:05:16 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pip(t_pip *pip, t_list *list)
{
	pip->exe = NULL;
	pip->size = ft_lstsize(list);
	pip->i = -1;
	pip->fd = malloc((sizeof(int *) * pip->size + 1));
	while (++(pip->i) < pip->size)
	{
		pip->fd[pip->i] = malloc(sizeof(int) * 2);
		pipe(pip->fd[pip->i]);
	}
	pip->i = -1;
}

void	free_fd(t_pip pip)
{
	int		i;

	if (pip.fd == NULL)
	{
		return ;
	}
	i = 0;
	while (i < pip.size)
	{
		close(pip.fd[i][1]);
		close(pip.fd[i][0]);
		free(pip.fd[i]);
		i++;
	}
	free(pip.fd);
}

t_list	*ft_pipe(t_list *list)
{
	t_pip	pip;

	set_pip(&pip, list);
	while (++(pip.i) < pip.size && ((t_command *)(list)->content))
	{
		pip.pid = fork();
		if (pip.pid == 0)
			do_son(list, pip);
		wait(&pip.status);
		g_data.status = WEXITSTATUS(g_data.status);
		close(pip.fd[pip.i][1]);
		while_3456(&list, &(pip.i));
		if ((list)->next)
			list = (list)->next;
		else if (((t_command *)(list)->content)->next_flag == 0)
			break ;
	}
	pip.i = -1;
	free_fd(pip);
	return (list);
}

void	if_type(t_command *content, t_command *next_con)
{
	if (ft_strncmp(content->type, ";", 2) == 0)
	{
		content->next_flag = 1;
		next_con->pre_flag = 1;
	}
	if (ft_strncmp(content->type, "|", 2) == 0)
	{
		content->next_flag = 2;
		next_con->pre_flag = 2;
	}
	if (ft_strncmp(content->type, ">", 2) == 0)
	{
		content->next_flag = 3;
		next_con->pre_flag = 3;
	}
	if (ft_strncmp(content->type, ">>", 3) == 0)
	{
		content->next_flag = 4;
		next_con->pre_flag = 4;
	}
	if (ft_strncmp(content->type, "<", 2) == 0)
	{
		content->next_flag = 5;
		next_con->pre_flag = 5;
	}
}

void	set_flag(t_list *i_list)
{
	t_list		*list;
	t_command	*content;
	t_command	*next_con;

	list = i_list;
	while (list->next)
	{
		content = (t_command *)list->content;
		next_con = (t_command *)list->next->content;
		if_type(content, next_con);
		if (ft_strncmp(content->type, "<<", 2) == 0)
		{
			content->next_flag = 6;
			next_con->pre_flag = 6;
		}
		if (list->next)
			list = list->next;
	}
}
