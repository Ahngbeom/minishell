/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:31:09 by bahn              #+#    #+#             */
/*   Updated: 2022/01/06 21:08:46 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backslash_converter(char **arg)
{
	char	*back_slash;
	char	*temp;
	char	*temp2;

	back_slash = NULL;
	back_slash = ft_strchr(*arg, '\\');
	while (back_slash != NULL)
	{
		temp = ft_substr(*arg, 0, back_slash - *arg);
		temp2 = ft_substr(*arg, back_slash - *arg + 1, ft_strlen(*arg));
		free(*arg);
		*arg = ft_strjoin(temp, temp2);
		free(temp);
		free(temp2);
		back_slash = ft_strchr(*arg, '\\');
	}
}
