/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:04:33 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/10 18:41:27 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*fill_d_struct(char *line, int *index, char *str, int *row)
{
	int		sign;

	sign = line[*index];
	*index += 1;
	while (line[*index] && line[*index] != sign)
	{
		str[*row] = line[*index];
		*index += 1;
		*row += 1;
	}
	*index += 1;
	return (str);
}

char	*fill_struct(char *line, int *index, char *str, int *row)
{
	if (check_condition(line[*index]))
	{
		while (check_condition(line[*index]))
		{
			str[*row] = line[*index];
			*index += 1;
			*row += 1;
		}
	}
	return (str);
}

void	allocate_fill_arg(char *line, t_cmd *data, int count_arg)
{
	int	index;
	int	col;
	int	row;

	index = 0;
	col = 0;
	data->arg = (char **)malloc(sizeof(char *) * (count_arg + 1));
	while (line[index])
	{
		row = 0;
		index = ignore_space(line, index);
		if (line[index] == '<' || line[index] == '>')
			index = skip_redirecition(line, index);
		index = ignore_space(line, index);
		if (line[index] && !is_metachar(line[index]))
		{
			data->arg[col] = fill_help(line, &index, &row);
			col++;
		}
	}
	data->arg[col] = NULL;
}
