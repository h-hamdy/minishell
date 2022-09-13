/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_her.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:05:20 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/11 16:55:17 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	allocate_fill_her(char *line, t_cmd *data, int count_her)
{
	int		index;
	int		col;
	int		row;

	index = 0;
	col = 0;
	data->limiter = (char **)malloc(sizeof(char *) * (count_her + 1));
	while (line[index])
	{
		row = 0;
		if (line[index] == '<' && line[index + 1] == '<')
		{
			index += 2;
			data->limiter[col] = fill_help(line, &index, &row);
			col++;
		}
		else
			index++;
	}
	data->limiter[col] = NULL;
}
