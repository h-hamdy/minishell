/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:06:56 by hhamdy            #+#    #+#             */
/*   Updated: 2022/06/25 07:38:39 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_redirection(char *line)
{
	int	i;
	int count;

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
		i++;
	}
	return (count);
}

int	count_herdoc(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = skip_char_inside_quote(line, i, 1);
		if (line[i] == '<' && line[i + 1] == '<')
			count++;
		i++;
	}
	return (count);
}

int	check_cmd(char *line, int flag)
{
	int index;
	int count;
	int c_quote;

	index = 0;
	count = 0;
	c_quote = 0;
	while (line[index])
	{
		index = ignore_space(line, index);
		if (line[index] == '<' || line[index] == '>')
			index = skip_redirecition(line, index);
		if (line[index] && line[index] != '<' && line[index] != '>' && line[index] != ' ')
		{
			if (flag == 1)
				return (index);
			while (line[index] && line[index] != '<' && line[index] != '>' && line[index] != ' ')
			{
				if (line[index] == '"' || line[index] == '\'')
				{
					while (line[index] && (line[index] != '"' || line[index] != '\''))
					{
						count++;
						index++;
					}
					return (count);
				}
				count++;
				index++;
			}
			return (count);
		}
	}
	return (count);
}

int count_args(char *line)
{
	int count;
	int index;

	count = 0;
	index = 0;
	while (line[index])
	{
		// if (line[index] == '"' || line[index] == '\'')
		// 	index = skip_char_inside_quote(line, index, 1);
		index = ignore_space(line, index);
		 if (line[index] == '<' || line[index] == '>')
			index = skip_redirecition(line, index);
		index = ignore_space(line, index);
		if (line[index] && (line[index] != '<' || line[index] != '>'))
		{
			if (line[index] == '"' || line[index] == '\'')
				index++;
			count++;
			while (line[index] && line[index] != '<' && line[index] != '>' && line[index] != ' ' && line[index] != '"' && line[index] != '\'')
				index++;
		}
		else
			index++;
	}
	return (count - 1);
}

int	  skip_redirecition(char *line, int index)
{
	index++;
	if (line[index] == '<' || line[index] == '>')
		index++;
	index = ignore_space(line, index);
	if (line[index] == '"' || line[index] == '\'')
	{
		if (line[index] == '"')
		{
			index++;
			while (line[index] && line[index] != '"')
				index++;
			return (index + 1);
		}
		else
		{
			index++;
			while (line[index] && line[index] != '\'')
				index++;
			return (index + 1);
		}
	}
	while (line[index] && line[index] != '<' && line[index] != '>' && line[index] != ' ' && line[index] != '"' && line[index] != '\'')
		index++;
	return (index);
}

int	skip_word(char *line, int index, int flag)
{
	if (flag == 1)
	{
		if (line[index] == '"')
		{
			index++;
			while (line[index] && line[index] != '"')
				index++;
		}
		else
		{
			index++;
			while (line[index] && line[index] != '\'')
				index++;
		}
		return (index);
	}
	while (line[index] && line[index] != '<' && line[index] != '>' && line[index] != ' ' && line[index] != '"')
		index++;
	return (index);
}