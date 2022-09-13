/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:28:53 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/01 07:59:18 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_redirection(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = skip_char_inside_quote(line, i, 1);
		if (line[i] == '<' && line[i + 1] == '<')
			i += 2;
		if (line[i] == '>' && line[i + 1] == '>')
		{
			count++;
			i += 2;
		}
		if ((line[i] == '>' && line[i + 1] != '>')
			|| (line[i] == '<' && line[i + 1] != '<'))
			count++;
		if (line[i])
			i++;
	}
	return (count);
}

int	count_herdoc(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = skip_char_inside_quote(line, i, 1);
		if (line[i] == '<' && line[i + 1] == '<')
			count++;
		if (line[i])
			i++;
	}
	return (count);
}

int	count_args(char *line)
{
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (line[index])
	{
		index = ignore_space(line, index);
		if (line[index] == '<' || line[index] == '>')
			index = skip_redirecition(line, index);
		index = ignore_space(line, index);
		if (line[index] && line[index] != '<' && line[index] != '>')
		{
			if (line[index] == '"' || line[index] == '\'')
				index = skip_double_quote(line, index, &count);
			else
				index = skip_single_quote(line, index, &count);
		}
		else if (line[index] && !is_metachar(line[index]))
			index++;
	}
	return (count);
}

int	ft_skip_word(char *line, int index, int *count)
{
	char	sign;

	sign = line[index];
	index++;
	while (line[index] && line[index] != sign)
	{
		*count = *count + 1;
		index++;
	}
	index++;
	return (index);
}

int	ft_count_word(char *line, int index)
{
	int		count;

	count = 0;
	while (1)
	{
		if (is_quote(line[index]))
			index = ft_skip_word(line, index, &count);
		if (line[index] && !is_quote(line[index])
			&& !is_metachar(line[index]) && line[index] != ' ')
		{
			while (line[index] && !is_quote(line[index])
				&& !is_metachar(line[index]) && line[index] != ' ')
			{
				count++;
				index++;
			}
		}
		if (!is_quote(line[index]))
			break ;
	}
	return (count);
}
