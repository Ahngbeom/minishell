/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:18:02 by bahn              #+#    #+#             */
/*   Updated: 2022/01/15 13:53:14 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redirection(void)
{
	g_data.arr_redirect = ft_calloc(sizeof(char *), 7);
	// g_data.arr_redirect[0] = ft_strdup("|");
	// g_data.arr_redirect[1] = ft_strdup(">>");
	// g_data.arr_redirect[2] = ft_strdup("<<");
	// g_data.arr_redirect[3] = ft_strdup(">");
	// g_data.arr_redirect[4] = ft_strdup("<");
	// g_data.arr_redirect[5] = NULL;
	g_data.arr_redirect[0] = SEMI_COLON;
	g_data.arr_redirect[1] = PIPE;
	g_data.arr_redirect[2] = TRNC_REDIR;
	g_data.arr_redirect[3] = APND_REDIR;
	g_data.arr_redirect[4] = R_TRNC_REDIR;
	g_data.arr_redirect[5] = R_APND_REDIR;
}
