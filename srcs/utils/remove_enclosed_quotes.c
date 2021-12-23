/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_enclosed_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:30:34 by bahn              #+#    #+#             */
/*   Updated: 2021/12/23 15:03:21 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_enclosed_quotes(char *argv)
{
	char	*more_input;
	char	*result;
	
	// Redirection
	if (argv == NULL)
		return (argv);
	while (ft_strchr(argv, '\"') == ft_strrchr(argv, '\"') && \
			ft_strchr(argv, '\'') == ft_strrchr(argv, '\''))
	{
		more_input = readline("> ");
		
	}
	result = ft_strtrim(argv, "\"\'");
	free(argv);
	return (result);
}
