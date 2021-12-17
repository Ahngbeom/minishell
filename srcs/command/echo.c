/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:46:46 by bahn              #+#    #+#             */
/*   Updated: 2021/12/17 18:59:46 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_echo(void)
{
	int		i;
	int		j;
	char	*temp;
	
	i = 0;
	while (g_data.argv[++i] != NULL)
	{
		if (!ft_strncmp(g_data.argv[i], "-n", ft_strlen("-n") + 1))
			continue ;
		else
		{
			temp = g_data.argv[i];
			g_data.argv[i] = ft_strtrim(g_data.argv[i], "\"\'");
			free(temp);
		}
		j = -1;
		while (g_data.argv[i][++j] != '\0' && g_data.argv[i][j] != ';')
		{
			if (g_data.argv[i][j] == '\\' && !ft_isalnum(g_data.argv[i][j + 1]))
				ft_putchar_fd(g_data.argv[i][++j], 1);
			else if (g_data.argv[i][j] == '$')
			{
				temp = g_data.argv[i];
				g_data.argv[i] = ft_strtrim(g_data.argv[i], "$");
				free(temp);
				ft_putstr_fd(getenv(g_data.argv[i]), 1);
				// export 명령어로 인해 변경된 env를 적용시켜야함
				// history 명령어도 적용되는지 확인 필요 -> 적용됨! 다행!
				break ;
			}
			else if (!ft_isalnum(g_data.argv[i][j]))
				continue ;
			else
				ft_putchar_fd(g_data.argv[i][j], 1);
		}
		// if (g_data.argv[i][j] == ';')
		// 	minishell_run(j + 1);
		if (g_data.argv[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (g_data.argv[1] == NULL || ft_strncmp(g_data.argv[1], "-n", ft_strlen("-n") + 1))
		ft_putchar_fd('\n', 1);
	return (SELF_PROC);
}

/********************************
 This Function is For execve()
********************************/
int	minishell_echo_for_execve(void)
{
	if (argv_counter(g_data.argv) == 1)
		return (0);
	else if (ft_strncmp(g_data.argv[1], "-n", ft_strlen("-n") + 1) == 0)
	{
		if (argv_counter(g_data.argv) == 2)
			return (0);
		else if (g_data.argv[2][0] != '\'' && g_data.argv[2][0] != '\"')
			return (0);
		else
			return (then_input(2, g_data.argv[2][0]));
	}
	else if (g_data.argv[1][0] == '\'' || g_data.argv[1][0] == '\"')
		return (then_input(1, g_data.argv[1][0]));
	else
		return (envvar_checker());
}
