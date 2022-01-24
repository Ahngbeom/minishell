/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:58:58 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 13:13:16 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	if (g_data.prompt != NULL)
		free(g_data.prompt);
	g_data.prompt = ft_strjoin_with_free(\
						ft_strdup("minishell:"), \
						getcwd(NULL, 0));
	g_data.prompt = ft_strjoin_with_free(g_data.prompt, ft_strdup("$ "));
	return (g_data.prompt);
}
