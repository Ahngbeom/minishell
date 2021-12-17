/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:08:21 by bahn              #+#    #+#             */
/*   Updated: 2021/12/17 16:18:45 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_env(void)
{
	int	i;

	i = -1;
	while (g_data.env[++i] != NULL)
		ft_putendl_fd(g_data.env[i], 1);
	return (SELF_PROC);
}

// For t_list
int		minishell_env2(void)
{
	t_list	*ptr;

	ptr = *g_data.envv;
	while (ptr != NULL)
	{
		ft_putstr_fd(((t_hash *)ptr->content)->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(((t_hash *)ptr->content)->value, 1);
		ptr = ptr->next;
	}
	return (SELF_PROC);
}

char	*env_getvalue(char *key)
{
	char	**temp;
	int		i;

	i = -1;
	while (g_data.env[++i] != NULL)
	{
		temp = ft_split(g_data.env[i], '=');
		if (!ft_strncmp(temp[0], key, ft_strlen(key) + 1))
		{
			split_free(temp);
			return (ft_strchr(g_data.env[i], '=') + 1);
		}
	}
	return (NULL);
}

//	For t_list
char	*env_getvalue2(char *key)
{
	t_list	*ptr;

	ptr = *g_data.envv;
	while (ptr != NULL)
	{
		if (!ft_strncmp(((t_hash *)ptr->content)->key, key, ft_strlen(key) + 1))
			return (((t_hash *)ptr->content)->value);
		ptr = ptr->next;
	}
	return (NULL);
}

char	**set_env(char *env[])
{
	char	**env_dupl;
	int		env_len;
	int		i;

	env_len = 0;
	while (env[env_len] != NULL)
		env_len++;
	env_dupl = ft_calloc(sizeof(char *), env_len + 1);
	if (env_dupl == NULL)
		exit(EXIT_FAILURE);
	i = -1;
	while (env[++i] != NULL)
		env_dupl[i] = ft_strdup(env[i]);
	env_dupl[i] = NULL;
	return (env_dupl);
}

t_list	**set_env2(char *env[])
{
	t_list	**lst;
	t_hash	*hash;
	char	**temp;
	int		env_len;
	int		i;

	i = -1;
	env_len = 0;
	while (env[++i] != NULL)
		env_len++;
	lst = ft_calloc(sizeof(t_list *), env_len);
	i = -1;
	while (env[++i] != NULL)
	{
		temp = ft_split(env[i], '=');
		hash = ft_calloc(sizeof(t_hash), 1);
		hash->key = temp[0];
		hash->value = temp[1];
		free(temp);
		ft_lstadd_back(lst, ft_lstnew(hash));
	}
	return (lst);
}

void	free_env(char *env[])
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		free(env[i]);
	free(env);
}

/****************
   Not used now
****************/
int	envvar_checker(void)
{
	char	*temp;
	int		i;
	int		j;
	
	if (argv_counter(g_data.argv) == 2 && g_data.argv[1][0] == '$')
	{
		temp = ft_strtrim(g_data.argv[1], "$\n");
		ft_split(g_data.argv[1], LF);
		if (getenv(temp))
			printf("%s\n", getenv(temp));
		else
		{
			printf("\n");
		}
		free(temp);
		return (-1);
	}
	else if (argv_counter(g_data.argv) == 3 && g_data.argv[2][0] == '$')
	{
		temp = ft_strtrim(g_data.argv[2], "$\n");
		if (getenv(temp))
			printf("%s\n", getenv(temp));
		else
			printf("\n");
		free(temp);
		return (-1);
	}
	else
	{
		i = 0;
		while (g_data.argv[++i] != NULL)
		{
			j = -1;
			while (g_data.argv[i][++j] != '\0')
			{
				printf("-n\n");
				if (g_data.argv[i][j] == '\\' && ft_isprint(g_data.argv[i][j + 1]))
					ft_putchar_fd(g_data.argv[i][++j], 1);
				else
					ft_putchar_fd(g_data.argv[i][j], 1);
			}
			if (g_data.argv[i + 1] != NULL)
				ft_putchar_fd(' ', 1);
		}
		if (g_data.argv[1] != NULL && ft_strncmp(g_data.argv[1], "-n", ft_strlen("-n")))
			ft_putchar_fd('\n', 1);
		return (-1);
	}
}