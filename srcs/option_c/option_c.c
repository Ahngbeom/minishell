/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:51:59 by bahn              #+#    #+#             */
/*   Updated: 2022/01/13 16:10:52 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	option_c(int argc, char *argv[])
{
	int		i;
	char	*input;
	char	*temp;

	if (argc > 1 && !ft_strncmp(argv[1], "-c", ft_strlen("-c") + 1))
	{
		if (argc > 2)
		{
			input = NULL;
			i = 1;
			while (++i < argc)
			{
				if (i + 1 >= argc)
				{
					if (input == NULL)
						input = ft_strdup(argv[i]);
					else
					{
						temp = ft_strjoin(input, " ");
						input = ft_strjoin(temp, argv[i]);
						free(temp);
					}
				}
				else
				{
					temp = ft_strjoin(argv[i], " ");
					input = ft_strjoin(temp, argv[++i]);
					free(temp);
				}
			}
			minishell(input);
		}
		minishell_finalize();
		exit(g_data.exit_stat);
	}
}
