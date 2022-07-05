/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:06:56 by hhamdy            #+#    #+#             */
/*   Updated: 2022/07/04 15:55:29 by hhamdy           ###   ########.fr       */
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

int  count_args(char *line)
{
	int count;
	int index;

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
			{
				while (1)
				{
					if (line[index] && (line[index] == '"' || line[index] == '\''))
						index = skip_word(line, index, 1) + 1;
					if (line[index] && line[index] != '"' && line[index] != '\'' && !is_metachar(line[index]) && line[index] != ' ')
						index = skip_word(line, index, 0);
					else
						break ;
				}
				count++;
			}
			else
			{
				while (line[index] && !is_metachar(line[index]) && line[index] != ' ' && line[index] != '"' && line[index] != '\'')
					index++;
				if (line[index] != '"' && line[index] != '\'')
					count++;
			}
		}
		else if (line[index] && !is_metachar(line[index]))
			index++;
	}
	return (count);
}

int	  skip_redirecition(char *line, int index)
{
	index++;
	if (line[index] == '<' || line[index] == '>')
		index++;
	index = ignore_space(line, index);
	while (1)
	{
		if (line[index] && (line[index] == '"' || line[index] == '\''))
			index = skip_word(line, index, 1) + 1;
		if (line[index] && line[index] != '"' && line[index] != '\'' && line[index] != '<' && line[index] != '>' && line[index] != ' ')
			index = skip_word(line, index, 0);
		if (line[index] != '"' && line[index] != '\'')
			break ;
	}
	return (index);
}

int	skip_word(char *line, int index, int flag)
{
	char sign;

	sign = 0;
	if (flag == 1)
	{
		sign = line[index];
		index++;
		while (line[index] && line[index] != sign)
			index++;
		return (index);
	}
	while (line[index] && line[index] != '<' && line[index] != '>' && line[index] != ' ' && line[index] != '"')
		index++;
	return (index);
}

char	*find_line(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	int i;
	char *line;
	char *join;
	char **paths;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	line = find_line(envp);
	if (!line)
		return (NULL);
	paths = ft_split(line, ':');
	while (paths[i])
	{
		join = ft_strjoin(paths[i], "/");
		if (access(ft_strjoin(join, cmd), X_OK) == 0)
			return (ft_strjoin(join, cmd));
		i++;
	}
	d_free(paths);
	return (NULL);
}