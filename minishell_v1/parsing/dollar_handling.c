/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:06:32 by hhamdy            #+#    #+#             */
/*   Updated: 2022/07/08 18:35:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*count_word(char *line)
{
	char *holder;
	int	i;

	i = 0;
	if (!line)
	{
		printf("4\n");
		return (NULL);
	}
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			while (line[i] && line[i] != ' ')
				i++;		
		}
		i++;
	}
	holder = malloc(sizeof(char) * i + 1);
	if (!holder)
		return (0);
	return (holder);
}

int	find_space(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			return (i);
		i++;
	}
	return (0);
}

char	*find_equal_s(char *env)
{
	int		i;
	char	*ret;

	i = 0;
	while(env[i] && env[i] != '=')
	{
		ret = fo_strjoin(ret, env[i]);
		i++;
		
	}
	return (ret);
}

char	*handel_echo(char *line)
{
	int		i;
	int		j;
	char	*holder;
	char	*value;
	char	*tmp;

	i = 0;
	j = 0;
	printf("--->%s\n", line);
	holder = ft_strdup("");
	tmp = ft_strdup("");
	while (line[j])
	{
		if (line[j] == '\'')
			break ;
		j++;
	}
	while (line[i])
	{
		// if (line[i] == '\'')
		// 	holder = find_sing_q(line);
		if(line[i] == '$')
		{
			// if (ft_isdigit(line[i + 1]))
			// {
			// 	holder = fo_strjoin(holder, line[i + 1]);
			// 	break ;
			// }
			// tmp = for_quote(line, i);
			// j = 0;
			// if (tmp[j] == '$')
			// {
				// j++;
				// while (tmp[j])
					// holder = fo_strjoin(holder, tmp[j++]);
				i++;
				while (line[i])
					holder = fo_strjoin(holder, line[i++]);
				break;
			// }
		}
		else if (line[i] == '"')
		{
			printf("%s\n", line);
			return (0);
		}
		i++;
	}
	if (ft_isdigit(holder[0]))
		check_digits(line);
	value = rest_of_dollar(g_v.envp, holder);
	return (value);
}
