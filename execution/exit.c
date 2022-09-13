/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:52:04 by fbouanan          #+#    #+#             */
/*   Updated: 2022/06/04 15:52:06 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	simpel_atoi(char *str)
{
	size_t			i;
	unsigned long	n;
	int				mult;

	i = 0;
	mult = 1;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			mult *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (mult == 1 && n > (unsigned long)LONG_MAX)
			return (-1);
		else if (mult == -1 && n > (unsigned long)LONG_MAX + 1)
			return (0);
		n = n * 10 + (str[i++] - '0');
	}
	return (mult * (int)n);
}

void	ft_helper(t_list *pipeline)
{
	g_v.exit_code = 255;
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minshell: exit: ", 1);
	ft_putstr_fd(((t_cmd *)pipeline->content)->arg[1], 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	exit(g_v.exit_code);
}

void	check_args(t_list *pipeline)
{
	char	*str;

	str = ((t_cmd *)pipeline->content)->arg[1];
	if (((t_cmd *)pipeline->content)->arg[2])
	{
		g_v.exit_code = 1;
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: to many arguments\n", 1);
		return ;
	}
	else if (str)
	{
		if (str[0] == '1' && !str[1])
		{
			g_v.exit_code = simpel_atoi(str);
			ft_putstr_fd("exit\n", 1);
			exit (g_v.exit_code);
		}
		g_v.exit_code = ft_atoi(str);
		if (g_v.exit_code == 1)
			ft_helper(pipeline);
		ft_putstr_fd("exit\n", 1);
		exit (g_v.exit_code);
	}
}

void	ft_exit(t_list *pipeline)
{
	int	i;

	i = 0;
	if (!((t_cmd *)pipeline->content)->arg[1])
	{
		ft_putstr_fd("exit\n", 1);
		exit(g_v.exit_code);
	}
	else if (((t_cmd *)pipeline->content)->arg[1])
	{
		while (((t_cmd *)pipeline->content)->arg[1][i])
		{
			if (ft_isalpha(((t_cmd *)pipeline->content)->arg[1][i]))
			{
				g_v.exit_code = 255;
				ft_putstr_fd("exit\n", 1);
				ft_putstr_fd("minshell: exit: ", 1);
				ft_putstr_fd(((t_cmd *)pipeline->content)->arg[1], 1);
				ft_putstr_fd(": numeric argument required\n", 1);
				exit(g_v.exit_code);
			}
			i++;
		}
		check_args(pipeline);
	}
}
