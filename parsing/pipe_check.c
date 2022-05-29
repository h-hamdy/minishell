/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:09:56 by hhamdy            #+#    #+#             */
/*   Updated: 2022/05/29 16:45:20 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*skip_space(char *s)
{
	int		i;
	int		j;
	char	*s_line;

	i = 0;
	j = 0;
	s_line = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!s_line)
		return (NULL);
	while (s[i])
	{
		if (s[i] != ' ')
			s_line[j++] = s[i];
		i++;
	}
	s_line[j] = '\0';
	return (s_line);
}

void	skip_d_quote(char *line, int i, int flag)
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
}

void	skip_s_quote(char *line, int i, int flag)
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
}

int	skip_char_inside_quote(char *line, int i, int flag)
{
	if (line[i] == '"')
		skip_d_quote(line, i, flag);
	else if (line[i] == '\'')
		skip_s_quote(line, i, flag);
	return (i);
}

int	check_pipe_error(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = skip_char_inside_quote(line, i, 0);
		if (line[i] == '|')
		{
			i = ignore_space(line, i + 1);
			if (line[i] == '|')
			{
				error_msg("`||'");
				return (0);
			}
			if (line[i + 1] != '|')
				count++;
		}
		i++;
	}
	return (1);
}
