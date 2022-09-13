/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 06:01:33 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/10 18:09:30 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_value(char *value, char c, int *index)
{
	char	s[2];
	char	*tmp;

	s[0] = c;
	s[1] = '\0';
	tmp = value;
	value = ft_strjoin(value, s);
	*index = *index + 1;
	free(tmp);
	return (value);
}

char	*expand_exit_value(char *value, int *index)
{
	char	*exit_n;
	char	*tmp;

	*index = *index + 2;
	if (g_v.cmp_exit == 0)
		exit_n = ft_itoa(g_v.exit_code);
	else
		exit_n = ft_strdup("0");
	tmp = value;
	value = ft_strjoin(value, exit_n);
	free(tmp);
	free(exit_n);
	return (value);
}

char	*get_value(char *value, char *buff)
{
	char	*str;
	char	*tmp;

	str = find_line(g_v.envp, buff);
	if (str)
	{
		str = ft_strjoin("", &str[(int)ft_strlen(buff) + 1]);
		tmp = value;
		value = ft_strjoin(value, str);
		free(tmp);
		free(str);
	}
	free(buff);
	return (value);
}

char	*join_line(char *value, char *line, int *index, int *flag)
{
	if (line[*index] == '$'
		&& (line[*index + 1] == ' ' || line[*index + 1] == '\0'))
		value = join_value(value, '$', index);
	if (line[*index] == '$' && line[*index + 1] == '?')
		value = expand_exit_value(value, index);
	if (line[*index] && line[*index] == '$'
		&& (!ft_isalpha(line[*index + 1]) || line[*index + 1] != '_'
			|| ft_isdigit(line[*index + 1]) || line[*index + 1] == '$'))
	{
		*flag = 1;
		if (line[*index] == '$' && line[*index + 1] != '?')
			*index = *index + 1;
		if (ft_isdigit(line[*index]))
			*index = *index + 1;
	}
	else if ((line[*index] && *flag == 0)
		|| (line[*index] == '$' && line[*index + 1] == ' ')
		|| (line[*index] == '$' && line[*index + 1] == '?'))
		value = join_value(value, line[*index], index);
	return (value);
}

char	*expand(char *value, char *line, int *index, int *flag)
{
	char	*buff;
	int		count;

	*flag = 1;
	buff = NULL;
	if (line[*index] == '$' && line[*index + 1] == '$')
		*index = *index + 1;
	*index = *index + 1;
	count = *index;
	while (line[*index]
		&& ((ft_isalpha(line[*index]) \
		&& line[*index] != '$' && line[*index] != ' ') \
		|| line[*index] == '_'))
		*index = *index + 1;
	buff = ft_cpy(buff, &line[count], *index - count);
	if (buff)
		value = get_value(value, buff);
	return (value);
}
