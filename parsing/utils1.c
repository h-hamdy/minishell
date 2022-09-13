/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 07:10:09 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/10 18:40:58 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_cpy(char *dest, char *src, int len)
{
	int	index;

	index = 0;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	while (index < len)
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

char	*fill_help(char *line, int *index, int *row)
{
	int		count;
	char	*str;

	*index = ignore_space(line, *index);
	count = ft_count_word(line, *index);
	str = (char *)malloc(sizeof(char *) * count + 1);
	while (1)
	{
		if (is_quote(line[*index]))
			str = \
			fill_d_struct(line, index, str, row);
		str = \
		fill_struct(line, index, str, row);
		if (!line[*index] || (line[*index] != '"' && line[*index] != '\''))
			break ;
	}
	str[*row] = '\0';
	return (str);
}

int	skip_double_quote(char *line, int index, int *count)
{
	while (1)
	{
		if (line[index] && (line[index] == '"' || line[index] == '\''))
			index = skip_word(line, index, 1);
		if (line[index] && !is_quote(line[index])
			&& !is_metachar(line[index]) && !ft_isspace(line[index]))
			index = skip_word(line, index, 0);
		else
			break ;
	}
	*count = *count + 1;
	return (index);
}

int	skip_single_quote(char *line, int index, int *count)
{
	while (line[index] && !is_metachar(line[index])
		&& line[index] != ' ' && line[index] != '"' && line[index] != '\'')
		index++;
	if (line[index] != '"' && line[index] != '\'')
		*count = *count + 1;
	return (index);
}

int	skip_herdoc(char *line, int index)
{
	index += 2;
	index = ignore_space(line, index);
	while (1)
	{
		if (line[index] == '"' || line[index] == '\'')
			index = skip_word(line, index, 1) + 1;
		else
			index = skip_word(line, index, 0);
		if (!line[index] || line[index] == ' ' || is_metachar(line[index]))
			break ;
	}
	return (index);
}
