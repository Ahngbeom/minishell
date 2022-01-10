/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:46:46 by bahn              #+#    #+#             */
/*   Updated: 2022/01/10 20:02:11 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	n_flag_checker(char *arg)
{
	if (!ft_strncmp(arg, "-n", ft_strlen(arg) + 1))
		return (1);
	else
		return (0);
}

// static	int	envmark_checker(char *env)
// {
// 	if (*env == '$')
// 	{
// 		if (*(env + 1) == '?')
// 			ft_putstr_fd(g_data.exit_stat, 1);
// 		else
// 		{
// 			// Try echo $HOME@@@@ on bash and minishell
// 			// Try echo $HOME\ $HOME\\ on bash and minishell
// 			ft_putstr_fd(get_envv_value(ft_substr(env, 1, ft_strlen(env) - 1)), 1);
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

// static	int	backslash_checker(char *arg, int *ch_idx)
// {
// 	if (arg[*ch_idx] == '\\')
// 	{
// 		if (arg[*ch_idx + 1] == '\\' || 
// 				arg[*ch_idx + 1] == '\'' || 
// 					arg[*ch_idx + 1] == '\"')
// 		{
// 			*ch_idx += 1;
// 			return (1);
// 		}
// 		return (0);
// 	}
// 	else if (arg[*ch_idx] == '\\' || 
// 				arg[*ch_idx] == '\'' || 
// 					arg[*ch_idx] == '\"')
// 		return (0);
// 	else
// 		return (1);
// }

int	minishell_echo(t_command *command)
{
	int		i;

	command->bulit_in_flag = 1;
	i = 0;
	while (command->argv[++i] != NULL)
	{
		if (i == 1 && n_flag_checker(command->argv[i]))
			continue ;
		// Try echo "asd'asd"'
		ft_putstr_fd(command->argv[i], 1);
		if (command->argv[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (command->argv[1] == NULL || !(n_flag_checker(command->argv[1])))
		ft_putchar_fd('\n', 1);
	return (SELF_PROC);
}
