/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 07:23:15 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/01 08:00:09 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_line(char **envp, char *key)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, search_for_char(envp[i])))
		{
			if (search_for_char(envp[i]) != (int)ft_strlen(key))
				return (NULL);
			return (envp[i]);
		}
		i++;
	}
	return (NULL);
}

char	*skip_space(char *s)
{
	int		i;
	int		j;
	char	*s_line;

	i = 0;
	j = 0;
	s_line = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	while (s[i])
	{
		if (s[i] != ' ')
			s_line[j++] = s[i];
		i++;
	}
	s_line[j] = '\0';
	return (s_line);
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
