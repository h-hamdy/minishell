/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:40:21 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/01 08:00:05 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	return (c == '\n' || c == ' ' || c == '\t'
		|| c == '\r' || c == '\v' || c == '\f');
}

int	is_metachar(char c)
{
	return (c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	search_for_char(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=')
		i++;
	return (i);
}

int	ignore_space(char *line, int i)
{
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}
