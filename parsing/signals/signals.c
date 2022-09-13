/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:28:07 by fbouanan          #+#    #+#             */
/*   Updated: 2022/09/11 20:28:36 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handel_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_v.perm = 1;
		g_v.exit_code = 1;
		if (g_v.check_her)
			printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	signals(void)
{
	signal(SIGINT, handel_signal);
	signal(SIGQUIT, SIG_IGN);
}
