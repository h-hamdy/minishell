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

char    *get_key(char *s)
{
	char	*hold;
	int		i;

	i = 0;
	while (s[i])
		i++;
	hold = malloc(sizeof(char) * i + 1);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		hold[i] = s[i];
		i++;
	}
	hold[i + 1] = '\0';
	return (hold);
}

int	check_var(char *av)
{
	int	i;
	
	i = 0;
	if (!ft_strcmp(av, "''") || !ft_strcmp(av, """"))
		return (1);
	while (av[i])
	{
		if (!ft_isalpha(av[0]) || !ft_isalnum(av[i]) || av[i] == '$' || av[i] == '?')
			return (1);
		i++;
	}
	return (0);
}

void    ft_unset(t_list *pipeline)
{
	int 	i;
	int 	k;
	char	**tmp;

	i = 0;
	k = 0;
	if (!((t_cmd*)pipeline->content)->arg[k])
		return ;
	while (g_v.envp[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (g_v.envp[i])
	{
		tmp[i] = g_v.envp[i];
		i++;
	}
	while (((t_cmd*)pipeline->content)->arg[k])
	{
		i = 0;
		if (check_var(((t_cmd*)pipeline->content)->arg[k]))
		{
			printf("unset: `%s': not a valid identifier\n", ((t_cmd*)pipeline->content)->arg[k]);
			return ;
		}
		while (tmp[i])
		{
			if (!ft_strcmp(((t_cmd*)pipeline->content)->arg[k], get_key(tmp[i])))
			{
				tmp[i][0] = '\0';
				break ;
			}
			i++;
		}
		k++;
	}
	i = 0;
	while (tmp[i])
	{
		if (tmp[i][0] != '\0')
			printf("%s\n", tmp[i++]);
		else	
			i++;
	}
}

