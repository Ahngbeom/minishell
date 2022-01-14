/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:18:02 by bahn              #+#    #+#             */
/*   Updated: 2022/01/14 15:04:06 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redirection(void)
{
	g_data.arr_redirect = ft_calloc(sizeof(char *), 6);
	// g_data.arr_redirect[0] = ft_strdup("|");
	// g_data.arr_redirect[1] = ft_strdup(">>");
	// g_data.arr_redirect[2] = ft_strdup("<<");
	// g_data.arr_redirect[3] = ft_strdup(">");
	// g_data.arr_redirect[4] = ft_strdup("<");
	// g_data.arr_redirect[5] = NULL;
	g_data.arr_redirect[0] = PIPE;
	g_data.arr_redirect[1] = TRNC_REDIR;
	g_data.arr_redirect[2] = APND_REDIR;
	g_data.arr_redirect[3] = R_TRNC_REDIR;
	g_data.arr_redirect[4] = R_APND_REDIR;
	g_data.arr_redirect[5] = NULL;
}
