/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:57:58 by bahn              #+#    #+#             */
/*   Updated: 2022/01/17 01:18:12 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_for_pipe(t_list *list)
{
	int			input;
	int			output;
	char		buf[BUFSIZ];
	t_command	*curr_cmd;
	t_command	*next_cmd;

	input = open(g_data.input, O_CREAT | O_RDWR, S_IRWXU);
	output = open(g_data.output, O_RDWR, S_IRWXU);
	while (read(output, buf, BUFSIZ) > 0)
	{
		write(input, buf, BUFSIZ);
		ft_bzero(buf, BUFSIZ);
	}
	close(input);
	close(output);
	curr_cmd = list->content;
	next_cmd = list->next->content;
	if (!ft_strncmp(curr_cmd->type, PIPE, ft_strlen(PIPE)) || \
		!ft_strncmp(curr_cmd->type, TRNC_REDIR, ft_strlen(TRNC_REDIR)))
	{
		next_cmd->o_flag = O_CREAT | O_RDWR | O_TRUNC;
	}
	else if (!ft_strncmp(curr_cmd->type, APND_REDIR, ft_strlen(APND_REDIR)))
	{
		next_cmd->o_flag = O_CREAT | O_RDWR | O_APPEND;
	}
	// R_TRNC_REDIR
	// R_APND_REDIR
	next_cmd->argv = add_arguments(next_cmd->argv, g_data.input);
	next_cmd->argv = add_arguments(next_cmd->argv, "--text");
}
