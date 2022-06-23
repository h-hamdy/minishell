/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:06:20 by hhamdy            #+#    #+#             */
/*   Updated: 2022/06/22 01:36:09 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parcing_function(char **env)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("\033[0;36mMinishell$ \033[0;37m");
		if (!line)
		{
			printf("exit\n");
			exit (0);
		}
		add_history(line);
		error_handling(line, env);
		free(line);
	}
}
