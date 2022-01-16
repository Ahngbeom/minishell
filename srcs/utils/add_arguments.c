/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 00:37:20 by bahn              #+#    #+#             */
/*   Updated: 2022/01/17 00:45:07 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_arguments(char **argv, char *add)
{
	char	**new;
	int		i;

	new = ft_calloc(sizeof(char *), argv_counter(argv) + 2);
	i = -1;
	while (argv[++i] != NULL)
	{
		new[i] = argv[i];
	}
	new[i] = ft_strdup(add);
	free(argv);
	return (new);
}
