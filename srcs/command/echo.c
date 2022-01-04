/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:46:46 by bahn              #+#    #+#             */
/*   Updated: 2022/01/04 14:16:18 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	n_flag_checker(char *argv)
{
	int		j;
	
	if (argv[0] == '-')
	{
		j = 1;
		while (argv[j] == 'n' && argv[j] != '\0')
			j++;
		if (argv[j] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

static	int	envmark_checker(char *env)
{
	if (*env == '$')
	{
		// Try echo $HOME@@@@ on bash and minishell
		// Try echo $HOME\ $HOME\\ on bash and minishell
		ft_putstr_fd(get_envv_value(ft_substr(env, 1, ft_strlen(env) - 1)), 1);
		return (1);
	}
	return (0);
}

static	int		backslash_checker(char *arg, int *ch_idx)
{
	if (arg[*ch_idx] == '\\')
	{
		if (arg[*ch_idx + 1] == '\\' || \
				arg[*ch_idx + 1] == '\'' || \
					arg[*ch_idx + 1] == '\"')
		{
			*ch_idx += 1;
			return (1);
		}
		return (0);
	}
	else if (arg[*ch_idx] == '\\' || \
				arg[*ch_idx] == '\'' || \
					arg[*ch_idx] == '\"')
		return (0);
	else
		return (1);
}

int	minishell_echo(t_command *command)
{
	int		i;
	int		j;

	command->bulit_in_flag = 1;
	i = 0;
	while (command->argv[++i] != NULL)
	{
		command->argv[i] = remove_enclosed_quotes(command->argv[i]);
		if (i == 1 && n_flag_checker(command->argv[i]))
			continue ;
		j = -1;
		while (command->argv[i][++j] != '\0')
		{
			if (envmark_checker(command->argv[i]))
				break ;
			else if (backslash_checker(command->argv[i], &j)) // Try echo "asd'asd"'
				ft_putchar_fd(command->argv[i][j], 1);
			else
				continue;
		}
		if (command->argv[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (command->argv[1] == NULL || !(n_flag_checker(command->argv[1])))
		ft_putchar_fd('\n', 1);
	return (SELF_PROC);
}
