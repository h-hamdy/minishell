/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:09:56 by hhamdy            #+#    #+#             */
/*   Updated: 2022/05/25 19:45:10 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

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

int	skip_char_inside_quote(char *line, int i, int flag)
{
	if (line[i] == '"')
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
	else if (line[i] == '\'')
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
	return (i);
}

int	ignore_space(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}

int	check_pipe_error(char *line)
{
	int i;
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
				error_msg("Minishell: syntax error near unexpected token `||'\n");
				return (0);
			}
			if (line[i + 1] != '|')
				count++;
		}
		i++;
	}
	return (1);
}
