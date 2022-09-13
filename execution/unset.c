/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:52:31 by fbouanan          #+#    #+#             */
/*   Updated: 2022/06/04 15:52:36 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	g_v.hold = malloc(sizeof(char) * i + 1);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		g_v.hold[i] = s[i];
		i++;
	}
	g_v.hold[i] = '\0';
	return (g_v.hold);
}

int	check_var(char *av)
{
	int	i;

	i = 0;
	if (!ft_strcmp(av, "''") || !ft_strcmp(av, """"))
		return (1);
	while (av[i])
	{
		if (!ft_isalpha(av[0]) || !ft_isalnum(av[i])
			|| av[i] == '$' || av[i] == '?')
			return (1);
		i++;
	}
	return (0);
}

int	check_unset(char *arg)
{
	int		i;
	char	*hold;

	i = 0;
	while (g_v.envp[i])
	{
		hold = get_key(g_v.envp[i]);
		if (!ft_strcmp(hold, arg))
		{
			free(hold);
			return (0);
		}
		free(hold);
		i++;
	}
	return (1);
}

void	ft_unset(t_list *pipeline)
{
	int		i;
	int		k;
	char	**tmp;

	i = 0;
	k = 1;
	if (!((t_cmd *)pipeline->content)->arg[0])
	{
		g_v.exit_code = 0;
		return ;
	}
	while (g_v.envp[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (g_v.envp[++i])
		tmp[i] = g_v.envp[i];
	while (((t_cmd *)pipeline->content)->arg[k])
	{
		ft_unset_tool(pipeline, tmp, k);
		k++;
	}
	tmp[i] = NULL;
	free(g_v.envp);
	g_v.envp = tmp;
}
