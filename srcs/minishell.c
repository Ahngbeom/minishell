/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:56 by bahn              #+#    #+#             */
/*   Updated: 2021/12/21 14:52:34 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_free(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}

char	*input_gnl(char *input)
{
	char	*temp;
	int		i;

	i = 0;
	while (input[i] != '\0' && input[i] != ';')
		i++;
	temp = malloc(sizeof(char) * i);
	i = 0;
	while (input[i] != '\0' && input[i] != ';')
	{
		temp[i] = input[i];
		i++;
	}
	return (temp);
}

int	minishell(void)
{
	int	rtn;
	int	i;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	g_data.input = readline(prompt());
	if (g_data.input == NULL)
	{
		ft_putendl_fd("exit", 1);
		return (1);
	}
	g_data.split_input = ft_split(g_data.input, ';');
	i = -1;
	while (g_data.split_input[++i] != NULL)
	{
		if (!ft_strncmp(g_data.split_input[i], "\n", ft_strlen("\n") + 1))
			return (0);
		else if (!ft_strncmp(g_data.split_input[i], "exit", ft_strlen("exit") + 1))
		{
			if (g_data.split_input[i][4] == ' ' || !(g_data.split_input[i][4]))
				ft_putendl_fd("exit", 1);
			if (g_data.input[5]) // && counter(split_input) == 1
				printf("minishell: exit: %s: numeric argument required\n", g_data.split_input[i] + 5);
			return (1);
		}
		rtn = parsing(i);
		if (rtn < 0)
			printf("minishell: %s: command not found\n", g_data.split_input[i]);
		add_history(g_data.split_input[i]);
		free(g_data.split_input[i]);
		split_free(g_data.argv);
	}
	return (0);
}
