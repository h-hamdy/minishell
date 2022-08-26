/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:06:20 by hhamdy            #+#    #+#             */
/*   Updated: 2022/06/26 19:33:19 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parcing_function(char **env)
{
	char	*line;

	line = NULL;
	while (1)
	{
		signals();
		line = readline("Minishell$ ");
		if (!line)
		{
			printf("exit\n");
			return ;
		}
		add_history(line);
		error_handling(line, env);
		free(line);
	}
}
