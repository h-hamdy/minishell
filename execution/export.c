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
	return (table);
}

int	get_eq_s(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
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
	write_expo(sor_exp, value_h);
	free(value_h);
	return ;
}

void	free_old_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
}

void	ft_export(t_list *pipeline, t_exec *exec)
{
	char	**arg;

	arg = ((t_cmd *)pipeline->content)->arg;
	if (!arg[1])
	{
		only_export(g_v.envp);
		g_v.exit_code = 0;
		return ;
	}
	add_export(arg, pipeline, exec);
}
