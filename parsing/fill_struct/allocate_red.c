/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:03:35 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/10 18:41:36 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_her(char *line, int index)
{
	if (line[index] == '<' && line[index + 1] == '<')
	{
		index += 2;
		index = ignore_space(line, index);
		if (is_quote(line[index]))
			index = skip_word(line, index, 1);
		else
			index = skip_word(line, index, 0);
	}
	return (index);
}

void	type_of_red(char *line, t_cmd *data, int *index, int *c_type)
{
	data->type[*c_type] = check_red_type(line, *index);
	*c_type = *c_type + 1;
	*index = *index + 1;
	if (line[*index] == '>')
		*index = *index + 1;
}

void	init_variable(int *index, int *c_type, int *col)
{
	*index = 0;
	*c_type = 0;
	*col = 0;
}

void	allocate_fill_red(char *line, t_cmd *data, int count_red)
{
	int		index;
	int		c_type;
	int		row;
	int		col;

	init_variable(&index, &c_type, &col);
	data->red = (char **)malloc(sizeof(char *) * (count_red + 1));
	data->type = (int *)malloc(sizeof(int) * (count_red + 1));
	while (line[index])
	{
		row = 0;
		if (line[index] == '<' && line[index + 1] == '<')
			index = skip_her(line, index);
		if ((line[index] == '>' && line[index + 1] == '>')
			|| (is_metachar(line[index])))
		{
			type_of_red(line, data, &index, &c_type);
			data->red[col] = fill_help(line, &index, &row);
			col++;
		}
		else if (line[index])
			index++;
	}
	data->red[col] = NULL;
}
