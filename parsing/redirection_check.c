/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:01:33 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/06 22:43:26 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_red_type(char *line, int index)
{
	if (line[index] == '>' && line[index + 1] == '>')
		return (3);
	if (line[index] == '<' && line[index + 1] == '<')
		return (4);
	if (line[index] == '<')
		return (1);
	return (2);
}

// this function check the last character of the line
int	last_char(char **line, int i)
{
	char	*s_line;
	int		end;

	while (line[i])
		i++;
	end = i - 1;
	i = -1;
	while (line[++i])
	{
		s_line = skip_space(line[i]);
		if (s_line[ft_strlen(s_line) - 1] == '<'
			|| s_line[ft_strlen(s_line) - 1] == '>')
		{
			if (i == end)
			{
				error_msg ("`newline'");
				return (0);
			}
			error_msg("`|'");
			return (0);
		}
		free(s_line);
	}
	return (1);
}

int	check_redirection(char **s_line, int i, int j)
{
	char	err;

	if ((s_line[i][j] == '<' && s_line[i][j + 1] == '<')
		|| (s_line[i][j] == '>' && s_line[i][j + 1] == '>'))
	{
		j = ignore_space(s_line[i], j + 2);
		if (s_line[i][j] == '>' || s_line[i][j] == '<')
		{
			err = s_line[i][j];
			raise_err(err);
			return (0);
		}
	}
	else if (s_line[i][j] == '<' || s_line[i][j] == '>')
	{
		j = ignore_space(s_line[i], j + 1);
		if (s_line[i][j] == '<' || s_line[i][j] == '>')
		{
			err = s_line[i][j];
			raise_err(err);
			return (0);
		}
	}
	return (1);
}

int	redirection_error(char **s_line)
{
	int	i;
	int	j;

	i = 0;
	if (!last_char(s_line, i))
		return (0);
	while (s_line[i])
	{
		j = 0;
		while (s_line[i][j])
		{
			j = ignore_space(s_line[i], j);
			j = skip_char_inside_quote(s_line[i], j, 1);
			if (!check_redirection(s_line, i, j))
				return (0);
			if (s_line[i][j])
				j++;
		}
		i++;
	}
	return (1);
}
