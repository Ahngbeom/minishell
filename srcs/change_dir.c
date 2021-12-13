/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 21:58:54 by bahn              #+#    #+#             */
/*   Updated: 2021/12/13 22:00:14 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(void)
{
	if (argv_counter(g_data.argv) > 2)
		printf("minishell: cd: too many arguments\n");
	else if (!ft_strncmp(g_data.argv[1], "~", 1) || g_data.argv[1] == NULL)
	{
		// env HOME=/home/ahngbeom
		if (chdir(g_data.home_path) == -1)
			exit(EXIT_FAILURE);
	}
	else if (g_data.argv[1] != NULL)
	{	
		if (chdir(g_data.argv[1]) == -1)
			exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_FAILURE);
	free(g_data.pwd);
	g_data.pwd = getcwd(NULL, 0);
	return (0);
}
