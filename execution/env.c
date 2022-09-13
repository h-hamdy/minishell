/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:51:56 by fbouanan          #+#    #+#             */
/*   Updated: 2022/06/04 15:51:57 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_list *pipeline)
{
	int	i;

	i = 0;
	if (!((t_cmd *)pipeline->content)->arg[1])
	{
		while (g_v.envp[i])
		{
			if (g_v.envp[i][0] && get_eq_s(g_v.envp[i]))
			{
				ft_putstr_fd(g_v.envp[i], 1);
				ft_putstr_fd("\n", 1);
			}
			i++;
		}
		g_v.exit_code = 0;
	}
	else
	{
		g_v.exit_code = 127;
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(((t_cmd *)pipeline->content)->arg[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
