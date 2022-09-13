/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:47:19 by fbouanan          #+#    #+#             */
/*   Updated: 2022/08/27 18:47:22 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_export(char *name)
{
	int	i;

	if (name[0] != '_' && !ft_isalpha(name[0]))
		return (0);
	i = 1;
	while (name[i])
	{
		if (name[i] != '_' && !ft_isalnum(name[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_valid_export(t_list *pipeline, t_exec *exec, char *arg)
{
	int	i;
	int	j;

	i = 0;
	while (g_v.envp[i])
		i++;
	j = 0;
	while (((t_cmd *)pipeline->content)->arg[j])
		j++;
	exec->hold = malloc(sizeof(char *) * (i + j + 1));
	i = 0;
	while (g_v.envp[i])
	{
		exec->hold[i] = g_v.envp[i];
		i++;
	}
	j = 1;
	exec->hold[i++] = ft_strdup(arg);
	exec->hold[i] = NULL;
	free(g_v.envp);
	g_v.envp = exec->hold;
	g_v.exit_code = 0;
}

void	change_env(char	*new, char *key)
{
	int		i;
	char	*hold;

	i = 0;
	while (g_v.envp[i])
	{
		hold = get_key(g_v.envp[i]);
		if (!ft_strcmp(hold, key))
		{
			free(g_v.envp[i]);
			g_v.envp[i] = ft_strdup(new);
		}
		i++;
		free(hold);
	}
	free(key);
}

int	check_dup_key(char *key)
{
	int		i;
	char	*hold;

	i = 0;
	while (g_v.envp[i])
	{
		hold = get_key(g_v.envp[i]);
		if (!ft_strcmp(hold, key))
		{
			free(hold);
			return (1);
		}
		i++;
		free(hold);
	}
	return (0);
}

void	write_expo(char **sor_exp, char **value_h)
{
	int		i;

	i = -1;
	while (sor_exp[++i])
		write_expo_2(i, sor_exp, value_h);
}
