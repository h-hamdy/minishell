/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:51:48 by fbouanan          #+#    #+#             */
/*   Updated: 2022/06/04 15:51:50 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rest_echo(char **arg, int i, int flag)
{
	int	k;

	if (i > 1)
		flag = 1;
	k = 0;
	while (arg[i])
	{
		ft_putstr_fd(arg[i++], 1);
		if (arg[i])
			ft_putstr_fd(" ", 1);
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
}

void	ft_echo(t_list *pipeline)
{
	int		i;
	int		j;
	int		flag;
	char	**arg;

	arg = ((t_cmd *)pipeline->content)->arg;
	i = 1;
	if (!arg)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	while (arg[i] && arg[i][0] == '-' && (arg[i][1] == 'n'))
	{
		j = 1;
		while (arg[i][j] == 'n')
			j++;
		if (arg[i][j] != '\0')
			break ;
		i++;
	}
	flag = 0;
	rest_echo(arg, i, flag);
	g_v.exit_code = 0;
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
