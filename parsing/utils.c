/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:06:56 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/01 06:30:39 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_redirecition(char *line, int index)
{
	index++;
	if (line[index] == '<' || line[index] == '>')
		index++;
	index = ignore_space(line, index);
	while (1)
	{
		if (line[index] && is_quote(line[index]))
			index = skip_word(line, index, 1);
		if (line[index] && !is_quote(line[index]) && !is_metachar(line[index])
			&& !ft_isspace(line[index]))
			index = skip_word(line, index, 0);
		if (line[index] != '"' && line[index] != '\'')
			break ;
	}
	return (index);
}

int	skip_word(char *line, int index, int flag)
{
	char	sign;

	sign = 0;
	if (flag == 1)
	{
		sign = line[index];
		index++;
		while (line[index] && line[index] != sign)
			index++;
		return (index);
	}
	while (line[index] && !is_metachar(line[index]) && !ft_isspace(line[index])
		&& !is_quote(line[index]))
		index++;
	return (index);
}

char	*return_line(char **paths, char *cmd, char *join, char *tmp)
{
	char	*line;

	line = ft_strjoin(join, cmd);
	if (join)
		free(join);
	(d_free(paths), free(tmp));
	return (line);
}

char	*return_path(char **envp)
{
	int	i;

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
	int		i;
	char	*line;
	char	*join;
	char	**paths;
	char	*tmp;

	i = -1;
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	line = return_path(envp);
	if (!line)
		return (NULL);
	paths = ft_split(line, ':');
	while (paths[++i])
	{
		join = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(join, cmd);
		if (access(tmp, X_OK) == 0)
			return (return_line(paths, cmd, join, tmp));
		(free(tmp), free(join));
	}
	d_free(paths);
	return (NULL);
}
