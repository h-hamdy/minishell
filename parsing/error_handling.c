/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:05:42 by hhamdy            #+#    #+#             */
/*   Updated: 2022/05/25 19:39:21 by hhamdy           ###   ########.fr       */
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
	if (d_quote % 2 != 0 || s_quote % 2 != 0)
	{
		error_msg("Minishell: double quotes error\n");
		return (0);
	}
	return (1);
}

// This function the first and the last of the line
// And if there is only a redirection in the line
int	ft_check1(char *line)
{
	char *s_line;
	
	s_line = skip_space(line);
	if (s_line[0] == '|')
	{
		error_msg("Minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	if (s_line[ft_strlen(s_line) - 1] == '|'
		|| s_line[ft_strlen(s_line) - 1] == '<'
		|| s_line[ft_strlen(s_line) - 1] == '>')
	{
			error_msg("Minishell: syntax error near unexpected token `newline'\n");
			return (0);
	}
	return (1);
}

void	redirections(char *line)
{
	char **s_line;
	
	if (!ft_check1(line))
		return ;
	if (!check_pipe_error(line))
		return ;
	s_line = ft_split(line, '|');
	int i = 0;
	while (s_line[i])
	{
		printf("%s\n", s_line[i]);
		i++;
	}
}

void	error_handling(char *line)
{
	if (!double_quote(line))
		return ;
	redirections(line);
}
