/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   systax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:17:16 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 14:23:34 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_checker(char *input)
{
	if (!ft_isalnum(*input) && ft_isprint(*input) && \
		*input != '$' && *input != '/')
	{
		printf("minishell: syntax error near unexpected token `%c'\n", *input);
		add_history(input);
		if (input != NULL)
			free(input);
		return (1);
	}
	return (0);
}
