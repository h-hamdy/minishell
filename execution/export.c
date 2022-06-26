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

void	only_export(char **env)
{
	int		i;
	char	**sor_exp;

	i = 0;
	sor_exp = sorted_exp(env);
	while (sor_exp[i])
		printf("declare -x %s\n", sor_exp[i++]);
	return ;
}

void	ft_export(t_list *pipeline, t_exec *exec)
{
	int	i;
	int	j;

	i = 0;
	// j = 0;
	printf("here\n");
	//printf("*****|%s|\n", ((t_cmd*)pipeline->content)->arg[0]);
	if (!((t_cmd*)pipeline->content)->arg[i])
	{
		only_export(g_v.envp);
		return ;
	}
	while (((t_cmd*)pipeline->content)->arg[i])
	{
		if (!ft_isalpha(((t_cmd*)pipeline->content)->arg[i][0]))
		{
			printf("export: `%s': not a valid identifier\n", ((t_cmd*)pipeline->content)->arg[i]);
			return ;
		}
		j = 0;
		while (((t_cmd*)pipeline->content)->arg[i][j])
		{
			if (!ft_isalpha(((t_cmd*)pipeline->content)->arg[i][0]) || ((t_cmd*)pipeline->content)->arg[i][0] == '=')
			{
				printf("=====export: `%s': not a valid identifier\n", ((t_cmd*)pipeline->content)->arg[i]);
				return ;
			}
			// else if (!ft_isalnum(((t_cmd*)pipeline->content)->arg[i][j]))
			// 	((t_cmd*)pipeline->content)->arg[i][j] = 127;
			j++;
		}
		i++;
	}
	i = 0;
	while (g_v.envp[i])
		i++;
	exec->hold = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (g_v.envp[i])
	{
		exec->hold[i] = g_v.envp[i];
		i++;
	}
			//printf("---->|%s|\n", ((t_cmd*)pipeline->content)->arg[0]);
  // return ;
	exec->hold[i] = ((t_cmd*)pipeline->content)->arg[0];
	exec->hold[i + 1] = NULL;
	//free envp l9dima wahda wahda
	g_v.envp = exec->hold;
	i = 0;
	while (g_v.envp[i])
	{
		printf("%s\n", g_v.envp[i++]);
	}
}
