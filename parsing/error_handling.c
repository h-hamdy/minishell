/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:05:42 by hhamdy            #+#    #+#             */
/*   Updated: 2022/06/02 10:30:59 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_quote(int *i_quote, int *lock)
{
	*i_quote = *i_quote + 1;
	if (*i_quote == 2)
	{
		*lock = 0;
		*i_quote = 0;
	}
}

// this function check if there is unclosed quotes
int	double_quote(char *line)
{
	int	i;
	int	d_quote;
	int	s_quote;
	int	lock;

	i = -1;
	d_quote = 0;
	s_quote = 0;
	lock = 0;
	while (line[++i])
	{
		if (line[i] == '"' && lock != 1)
		{
			lock = 2;
			check_quote(&d_quote, &lock);
		}
		if (line[i] == '\'' && lock != 2)
		{
			lock = 1;
			check_quote(&s_quote, &lock);
		}
	}
	if (!trow_err(d_quote, s_quote))
		return (0);
	return (1);
}

// This function the first and the last of the line
int	pre_check(char *line)
{
	char	*s_line;

	s_line = skip_space(line);
	if (s_line[0] == '|' && s_line[1] != '|')
	{
		error_msg("`|'");
		return (0);
	}
	else if (s_line[ft_strlen(s_line) - 1] == '|')
	{
		error_msg("`newline'");
		return (0);
	}
	free(s_line);
	return (1);
}

int	redirections(char *line)
{
	char	**s_line;

	if (!pre_check(line))
		return (0);
	if (!check_pipe_error(line))
		return (0);
	s_line = ft_split(line, '|');
	if (!redirection_error(s_line))
		return (0);
	return (1);
}

void	error_handling(char *line, char **env)
{
	if (!double_quote(line))
		return ;
	if (!redirections(line))
		return ;
	handel_echo(line, env);
}
