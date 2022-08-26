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
	while (s[i] && s[i] != '=')
		i++;
	hold = malloc(sizeof(char) * i + 1);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		hold[i] = s[i];
		i++;
	}
	hold[i] = '\0';
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

		if (!ft_isalpha(av[0]) || !ft_isalnum(av[i]) || av[i] == '$' ||
			av[i] == '?')
			return (1);
		i++;
	}
	return (0);
}

void    ft_unset(t_list *pipeline)
{
	int 	i;
	int 	k;
	int		j;
	char	**tmp;
	i = 0;
	k = 1;
	if (!((t_cmd*)pipeline->content)->arg[0])
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
		j = 0;
		if (check_var(((t_cmd*)pipeline->content)->arg[k]))
		{
			// printf("unset: `%s': not a valid identifier\n", ((t_cmd*)pipeline->content)->arg[k]);
			ft_putstr_fd("unset: \'", 1);
			ft_putstr_fd(((t_cmd*)pipeline->content)->arg[k], 1);
			ft_putstr_fd("\': not a valid identifier\n", 1);
			return ;
		}
		while (tmp[j])
		{
			if (!ft_strcmp(((t_cmd*)pipeline->content)->arg[k], get_key(tmp[j])))
			{
				tmp[j][0] = '\0';
				break ;
			}
			j++;
		}
		k++;
	}
	tmp[i] = NULL;
	g_v.envp = tmp;
}

