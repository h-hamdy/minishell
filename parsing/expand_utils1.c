/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 07:00:15 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/06 19:09:17 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_s_quote(char *value, char *line, int *index)
{
	value = join_value(value, line[*index], index);
	while (line[*index] != '\'')
		value = join_value(value, line[*index], index);
	value = join_value(value, '\'', index);
	return (value);
}

char	*skip_herdoc_sign(char *value, int *index)
{
	value = join_value(value, '<', index);
	value = join_value(value, '<', index);
	return (value);
}

char	*get_buff(char *line, int *index)
{
	int		count;
	char	*buff;

	*index = *index + 1;
	buff = NULL;
	count = *index;
	while (line[*index] && !is_quote(line[*index])
		&& line[*index] != '$' && line[*index] != ' ')
		*index = *index + 1;
	buff = ft_cpy(buff, &line[count], *index - count);
	return (buff);
}

char	*expand_d_quote2(char *value, char *line, int *index)
{
	char	*buff;

	if (line[*index] == '\"')
		value = join_value(value, '"', index);
	if (line[*index] == '$' && (line[*index + 1] == ' ' \
		|| line[*index + 1] == '\0' || line[*index + 1] == '"'))
		value = join_value(value, '$', index);
	if (line[*index] == '$' && line[*index + 1] == '?')
		value = expand_exit_value(value, index);
	if (line[*index] == '$'
		&& (ft_isalpha(line[*index + 1]) || line[*index + 1] == '_'))
	{
		buff = get_buff(line, index);
		if (buff)
			value = get_value(value, buff);
	}
	return (value);
}

char	*expand_d_quote(char *value, char *line, int *index)
{
	while (1)
	{
		value = expand_d_quote2(value, line, index);
		if (line[*index] != '"' && line[*index] != '$')
			value = join_value(value, line[*index], index);
		if ((line[*index] == '$' \
			&& !ft_isalpha(line[*index + 1]) && line[*index + 1] != '_')
			|| (line[*index] == '$' && ft_isdigit(line[*index + 1])))
		{
			if (ft_isdigit(line[*index + 1]))
				*index = *index + 1;
			if (line[*index] == '$' && line[*index + 1] != '?')
				*index = *index + 1;
		}
		if (!line[*index] || line[*index] == '"')
			break ;
	}
	if (line[*index] == '\"')
		value = join_value(value, '"', index);
	return (value);
}
