/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_with_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:00:35 by bahn              #+#    #+#             */
/*   Updated: 2022/01/10 22:03:06 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_with_free(char *str1, char *str2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	if (!str1 || !str2)
		return (NULL);
	s1_len = ft_strlen((char *)str1);
	s2_len = ft_strlen((char *)str2);
	result = malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, (char *)str1, s1_len + 1);
	ft_strlcat(result, (char *)str2, s1_len + s2_len + 1);
	free(str1);
	free(str2);
	return (result);
}
