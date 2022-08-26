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

void	ft_echo(t_list *pipeline)
{
	int	i;
	int	j;
	int	k;
	int	flag;

	i = 1;
	if (!((t_cmd*)pipeline->content)->arg)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	while (((t_cmd*)pipeline->content)->arg[i] && ((t_cmd*)pipeline->content)->arg[i][0] == '-'
		&& ((t_cmd*)pipeline->content)->arg[i][1] == 'n')
	{
		j = 1;
		while (((t_cmd*)pipeline->content)->arg[i][j] == 'n')
			j++;
		if (((t_cmd*)pipeline->content)->arg[i][j] != '\0')
			break ;
		i++;
	}
	flag = 0;
	if (i > 1)
		flag = 1;
	while (((t_cmd*)pipeline->content)->arg[i])
	{
			k = 0;
		while (((t_cmd*)pipeline->content)->arg[i][k])
		{
			if (((t_cmd*)pipeline->content)->arg[i][k] == '$')
			{
				((t_cmd*)pipeline->content)->arg[i] = handel_echo(((t_cmd*)pipeline->content)->arg[i]);
				if (!((t_cmd*)pipeline->content)->arg[i])
					return ;
				break;
			}	
			k++;
		}
		ft_putstr_fd(((t_cmd*)pipeline->content)->arg[i], 1);
		i++;
		if (((t_cmd*)pipeline->content)->arg[i])
			ft_putstr_fd(" ", 1);
	}
	if (flag == 0)
		ft_putstr_fd("\n",1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
