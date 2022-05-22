/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:06:20 by hhamdy            #+#    #+#             */
/*   Updated: 2022/05/22 10:11:36 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *s)
{
	printf("%s", s);
}

void	double_quotes(char *line)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '"')
			flag++;
		i++;
	}
	if (flag % 2 != 0)
		error_msg("double quotes error\n");
}

void	split_line(char *line)
{
	double_quotes(line);
}

void	parcing_function(void)
{
	char	*line;

	while (1)
	{
		line = readline("\033[0;36mMinishell$ \033[0;37m");
        add_history(line);
		split_line(line);
	}
}
