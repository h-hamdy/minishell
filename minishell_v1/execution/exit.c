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

void    ft_exit(t_exec *exec)
{
	exec = NULL;
	// int i;

	// if (!exec->av[2])
	// {
	// 	printf("here\n");
	// 	exit(0);
	// }
	// i = 2;
	// while (exec->av[i])
	// {
	// 	i++;
	// }
	ft_putstr_fd("exit ", 1);
	ft_putnbr_fd(g_v.exit_code, 1);
	ft_putstr_fd("\n", 1);
	exit(0);
}