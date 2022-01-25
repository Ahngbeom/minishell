/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_with_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:47:03 by bahn              #+#    #+#             */
/*   Updated: 2022/01/24 20:26:49 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_with_free(char *src)
{
	int		i;
	int		src_len;
	char	*cpy;

	i = 0;
	src_len = ft_strlen(src);
	cpy = malloc(sizeof(char) * src_len + 1);
	if (!cpy)
		return (NULL);
	while (i < src_len)
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	free(src);
	return (cpy);
}
