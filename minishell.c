/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:23:57 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/06 22:50:22 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	global_v(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_v.envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		g_v.envp[i] = ft_strdup(env[i]);
		i++;
	}
	g_v.envp[i] = NULL;
	g_v.n_node = 0;
	g_v.check = 0;
	g_v.f_f = 0;
	g_v.check_her = 1;
	g_v.flag = 0;
}

int	main(int ac, char **av, char **envp)
{
	global_v(envp);
	(void)av;
	if (ac != 1 || !envp)
		return (0);
	parcing_function();
}
