/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 03:44:01 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/11 18:08:20 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*herdoc_d_quote(char *value, char *line, int *index)
{
	char	c;

	c = line[*index];
	*index += 1;
	while (line[*index] && line[*index] != c)
		value = join_value(value, line[*index], index);
	*index += 1;
	return (value);
}

char	*herdoc_expand(char *value, char *line, int *index)
{
	value = skip_herdoc_sign(value, index);
	while (1)
	{
		if (line[*index] == ' ')
		{
			value = join_value(value, line[*index], index);
			*index = ignore_space(line, *index);
		}
		if (is_quote(line[*index]))
			value = herdoc_d_quote(value, line, index);
		else if (line[*index] && !is_quote(line[*index]))
		{
			value = join_value(value, line[*index], index);
			while (line[*index] && !is_quote(line[*index])
				&& !is_metachar(line[*index]) && line[*index] != ' ')
				value = join_value(value, line[*index], index);
		}
		if (!line[*index] || (line[*index] != '"' && line[*index] != '\''))
			break ;
	}
	return (value);
}

char	*expand_dollar(char *line)
{
	char	*value;
	int		index;
	int		flag;

	index = 0;
	value = ft_strdup("");
	while (line[index])
	{
		flag = 0;
		if (line[index] == '\"')
			value = expand_d_quote(value, line, &index);
		else if (line[index] == '$'
			&& (ft_isalpha(line[index + 1]) || line[index + 1] == '_'))
			value = expand(value, line, &index, &flag);
		else
		{
			if (line[index] == '\'')
				value = get_s_quote(value, line, &index);
			else if (line[index] == '<' && line[index + 1] == '<')
				value = herdoc_expand(value, line, &index);
			else
				value = join_line(value, line, &index, &flag);
		}
	}
	return (value);
}
