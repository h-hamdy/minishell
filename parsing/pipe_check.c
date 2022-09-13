/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:09:56 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/01 06:49:06 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**replace_pipe(char **s_line)
{
	int	index;
	int	row;

	index = 0;
	while (s_line[index])
	{
		row = 0;
		while (s_line[index][row])
		{
			if (s_line[index][row] == -1)
				s_line[index][row] = '|';
			row++;
		}
		index++;
	}
	return (s_line);
}

int	skip_d_quote(char *line, int i, int flag)
{
	i++;
	while (line[i] && line[i] != '"')
	{
		if (flag == 0)
		{
			if (line[i] == '|')
				line[i] = -1;
		}
		i++;
	}
	return (i);
}

int	skip_s_quote(char *line, int i, int flag)
{
	i++;
	while (line[i] && line[i] != '\'')
	{
		if (flag == 0)
		{
			if (line[i] == '|')
				line[i] = -1;
		}
		i++;
	}
	return (i);
}

int	skip_char_inside_quote(char *line, int i, int flag)
{
	if (line[i] == '"')
		i = skip_d_quote(line, i, flag);
	else if (line[i] == '\'')
		i = skip_s_quote(line, i, flag);
	return (i);
}

int	check_pipe_error(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = skip_char_inside_quote(line, i, 0);
		if (line[i] == '|')
		{
			if (line[i + 1] == '|')
			{
				error_msg("`|'");
				return (0);
			}
			i = ignore_space(line, i + 1);
			if (line[i] == '|')
			{
				error_msg("`|'");
				return (0);
			}
		}
		else
			i++;
	}
	return (1);
}
