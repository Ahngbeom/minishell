/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:58:58 by bahn              #+#    #+#             */
/*   Updated: 2021/12/16 16:16:10 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	char	*temp;

	g_data.prompt = ft_strjoin("\e[1;32mminishell\e[0m:", g_data.current_path);
	temp = ft_strdup(g_data.prompt);
	free(g_data.prompt);
	g_data.prompt = ft_strjoin(temp, "$ ");
	free(temp);
	// g_data.prompt = ft_strdup("minishell 🚀 ");
	return (g_data.prompt);
}