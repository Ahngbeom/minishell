/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:18:02 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 01:20:36 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redirection(void)
{
	g_data.arr_redirect = ft_calloc(sizeof(char *), 7);
	g_data.arr_redirect[0] = SEMI_COLON;
	g_data.arr_redirect[1] = PIPE;
	g_data.arr_redirect[2] = APND_REDIR;
	g_data.arr_redirect[3] = R_APND_REDIR;
	g_data.arr_redirect[4] = TRNC_REDIR;
	g_data.arr_redirect[5] = R_TRNC_REDIR;
}
