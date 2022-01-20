/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:58:58 by bahn              #+#    #+#             */
/*   Updated: 2022/01/19 00:04:43 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	if (g_data.prompt != NULL)
		free(g_data.prompt);
	g_data.prompt = ft_strjoin_with_free(\
						ft_strdup("\e[1;32mminishell\e[0m:"), \
						getcwd(NULL, 0));
	g_data.prompt = ft_strjoin_with_free(g_data.prompt, ft_strdup("$ "));
	return (g_data.prompt);
}
