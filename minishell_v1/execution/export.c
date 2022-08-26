/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:52:13 by fbouanan          #+#    #+#             */
/*   Updated: 2022/06/04 15:52:14 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**sorted_exp(char **table)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (table[i])
	{
		j = i + 1;
		while (table[j])
		{
			if (ft_strcmp(table[i], table[j]) > 0)
			{
				tmp = table[i];
				table[i] = table[j];
				table[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	return (table);
}

int	get_eq_s(char *str)
{
	int		i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	only_export(char **env)
{
	int		i;
	char	**sor_exp;
	char	**value_h;

	i = 0;
	sor_exp = sorted_exp(env);
	while (sor_exp[i])
		i++;
	value_h = malloc(sizeof(char *) * (i + 1));
	if (!value_h)
		return ;
	i = 0;
	while (sor_exp[i])
	{
		value_h[i] = ft_strchr(sor_exp[i], '=') + 1;
		i++;
	}
	value_h[i] = NULL;
	i = 0;
	while (sor_exp[i])
	{
		if (sor_exp[i][0] == '\0')
			i++;
		else if (get_eq_s(sor_exp[i]))
		{
			// printf("%s=\"%s\"\n", get_key(sor_exp[i]));
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(get_key(sor_exp[i]), 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(value_h[i], 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
		{
			// printf("declare -x %s\n", get_key(sor_exp[i]));
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(get_key(sor_exp[i]), 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return ;
}

void	free_old_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		env = NULL;
		i++;
	}
}

void	ft_export(t_list *pipeline, t_exec *exec)
{
	int	i;
	int	j;

	i = 1;
	if (!((t_cmd*)pipeline->content)->arg[i])
	{
		only_export(g_v.envp);
		return ;
	}
	while (((t_cmd*)pipeline->content)->arg[i])
	{
		if (!ft_isalpha(((t_cmd*)pipeline->content)->arg[i][0]))
		{
			ft_putstr_fd("export: `", 1);
			ft_putstr_fd(((t_cmd*)pipeline->content)->arg[i], 1);
			ft_putstr_fd("\': not a valid identifier\n", 1);
			return ;
		}
		j = 0;
		while (((t_cmd*)pipeline->content)->arg[i][j])
		{
			if (!ft_isalpha(((t_cmd*)pipeline->content)->arg[i][0]) || ((t_cmd*)pipeline->content)->arg[i][0] == '=')
			{
				ft_putstr_fd("=====export: `", 1);
				ft_putstr_fd(((t_cmd*)pipeline->content)->arg[i], 1);
				ft_putstr_fd("\': not a valid identifier\n", 1);
				return ;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (g_v.envp[i])
		i++;
	j = 0;
	while (((t_cmd*)pipeline->content)->arg[j])
		j++;
	// printf("%d\n", j);
	exec->hold = malloc(sizeof(char *) * (i + j + 1));
	i = 0;
	while (g_v.envp[i])
	{
		exec->hold[i] = g_v.envp[i];
		i++;
	}
	j = 1;
	while (((t_cmd*)pipeline->content)->arg[j])
	{
		exec->hold[i] = ((t_cmd*)pipeline->content)->arg[j];
		i++;
		j++;
	}
	exec->hold[i] = NULL;
	//free envp l9dima wahda wahda
	//free_old_env(g_v.envp);
	g_v.envp = exec->hold;
}
