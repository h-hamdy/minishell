/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:40:21 by hhamdy            #+#    #+#             */
/*   Updated: 2022/06/25 02:21:42 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *msg)
{
	char	*str;

	str = ft_strjoin("Minishell: syntax error near unexpected token ", msg);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free(str);
}

int	ignore_space(char *line, int i)
{
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	trow_err(int d_quote, int s_quote)
{
	if (d_quote % 2 != 0 || s_quote % 2 != 0)
	{
		write(2, "Minishell: double quotes error\n", 32);
		return (0);
	}
	return (1);
}

char	**ft_free(char **str, int k)
{
	while (k >= 0)
	{
		free(str[k]);
		k--;
	}
	return (str);
}

void	d_free(char **str)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
	str = NULL;
}

char	*fo_strjoin(char *str, char c)
{
	char	*r;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
		i++;
	r = malloc(sizeof(char) * i + 2);
	if (!r)
		return (NULL);
	i = 0;
	while (str[i])
	{
		r[i] = str[i];
		i++;
	}
	r[i] = c;
	r[i + 1] = '\0';
	free(str);
	return (r);
}

int	ft_count_word(char *line, int index)
{
	int count;

	count = 0;
	if (line[index] == '"' || line[index] == '\'')
	{
		if (line[index] == '"')
		{
			index++;
			while (line[index] && line[index] != '"')
				(count++, index++);
		}
		else
		{
			index++;
			while (line[index] && line[index] != '\'')
				(count++, index++);
		}
		return (count);
	}
	else
	{
		while (line[index] && line[index] != ' ' && line[index] != '>' && line[index] != '<'
			&& line[index] != '"' && line[index] != '\'')
		{
			index++;
			count++;
		}
	}
	return (count);
}
