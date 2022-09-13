/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:06:20 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/11 20:28:25 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parcing_function(void)
{
	char	*line;
	t_list	*pipeline;
	t_list	*tmp;

	while (1)
	{
		signals();
		line = readline("Minishell$ ");
		if (!line)
		{
			printf("exit\n");
			exit (g_v.exit_code);
		}
		if (ft_strlen(line))
			add_history(line);
		pipeline = error_handling(line, g_v.envp);
		while (pipeline)
		{
			free_struct(pipeline);
			tmp = pipeline;
			pipeline = pipeline->next;
			free(tmp);
		}
		free(line);
	}
}
