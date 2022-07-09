/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:52:04 by fbouanan          #+#    #+#             */
/*   Updated: 2022/07/08 18:38:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_exit(t_exec *exec)
{
	(void)exec;
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
	printf("exit\n");
	exit(0);
}