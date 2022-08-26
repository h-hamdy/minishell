/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:23:57 by hhamdy            #+#    #+#             */
/*   Updated: 2022/06/25 04:03:13 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	global_v(char **env)
{
	g_v.envp = env;
	g_v.n_node = 0;
	// g_v.save0 = dup(0);
	// g_v.save1 = dup(1);
}

int	main(int ac, char **av, char **envp)
{
	global_v(envp);
	(void)ac;
	if (!av || !envp)
		return (0);
	parcing_function(envp);
}
