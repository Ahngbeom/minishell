/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:19:52 by bahn              #+#    #+#             */
/*   Updated: 2022/01/18 17:37:24 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_info(t_list *list, int on_off)
{
	t_list		*ptr;
	t_command	*cmd;
	int			i;

	if (on_off != 0)
	{
		printf("=======================================================\n");
		ptr = list;
		while (ptr != NULL)
		{
			printf("--------------------------------------------------------\n");
			cmd = ptr->content;
			i = -1;
			while (cmd->argv[++i] != NULL)
			{
				if (i == 0)
				{
					printf("Command : %s\n", cmd->argv[i]);
					printf("Argv : ");
				}
				else
					printf("%s ", cmd->argv[i]);
			}
			printf("NULL\n");
			printf("TYPE : %s\n", cmd->type);
			ptr = ptr->next;
			printf("--------------------------------------------------------\n");
		}
		printf("=======================================================\n");
	}
}
