/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:05:42 by hhamdy            #+#    #+#             */
/*   Updated: 2022/07/08 18:35:35 by marvin           ###   ########.fr       */
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
	if (!s_line[0])
		return (0);
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

char	**redirections(char *line)
{
	char	**s_line;

	s_line = NULL;
	if (!pre_check(line))
		return (NULL);
	if (!check_pipe_error(line))
		return (NULL);
	s_line = ft_split(line, '|');
	if (!redirection_error(s_line)) 
		return (NULL);
	return (s_line);
}

void	error_handling(char *line, char **env)
{
	char	**s_line;
	t_list	*pipeline;

	s_line = NULL;
	if (!double_quote(line))
		return ;
	s_line = redirections(line);
	if (!s_line)
		return ;
	// handel_echo(line, env);
	pipeline = get_full_cmd(s_line, env);
	if (!pipeline)
		return ;
	int i = 0;
	while (pipeline)
	{
		if (((t_cmd*)pipeline->content)->limiter)
		{
			i = 0;
			while (((t_cmd*)pipeline->content)->limiter[i])
			{
				printf("limiter = |%s|\n", ((t_cmd*)pipeline->content)->limiter[i]);
				i++;
			}
		}
		if (((t_cmd*)pipeline->content)->red)
		{
			i = 0;
			while (((t_cmd*)pipeline->content)->red[i])
			{
				printf("red = |%s| and type = |%d|\n", ((t_cmd*)pipeline->content)->red[i], ((t_cmd*)pipeline->content)->type[i]);
				i++;
			}
		}
		if (((t_cmd*)pipeline->content)->cmd)
			 printf("cmd = |%s|\n", ((t_cmd*)pipeline->content)->cmd);
		if (((t_cmd*)pipeline->content)->cmd_path)
			 printf("cmd_path = |%s|\n", ((t_cmd*)pipeline->content)->cmd_path);
		if (((t_cmd*)pipeline->content)->arg)
		{
			i = 0;
			while (((t_cmd*)pipeline->content)->arg[i])
			{
				printf("arg = |%s|\n", ((t_cmd*)pipeline->content)->arg[i]);
				i++;
			}
		}
		// builtins(pipeline, env);
		pipeline = pipeline->next;
		printf("------------------------------------\n");
	}
	d_free(s_line);
}
