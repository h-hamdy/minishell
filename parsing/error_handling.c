/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:05:42 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/09 03:04:49 by hhamdy           ###   ########.fr       */
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
	{
		free(s_line);
		return (0);
	}
	else if (s_line[ft_strlen(s_line) - 1] == '|' || s_line[0] == '|')
	{
		if (s_line[0] == '|')
			error_msg("`|'");
		else
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
	if (!s_line)
		return (NULL);
	if (!redirection_error(s_line))
		return (NULL);
	replace_pipe(s_line);
	return (s_line);
}

t_list	*error_handling(char *line, char **env)
{
	char	**s_line;
	t_list	*pipeline;
	t_list	*head;
	int		fd[2];

	(void)env;
	g_v.perm = 0;
	g_v.sig = 0;
	g_v.ret = 1;
	g_v.dup_1 = dup(1);
	s_line = NULL;
	if (!double_quote(line))
		return (NULL);
	s_line = redirections(line);
	if (!s_line)
		return (NULL);
	pipeline = get_full_cmd(s_line, env);
	d_free(s_line);
	if (!pipeline)
		return (NULL);
	g_v.dup_0 = dup(0);
	g_v.n_node = ft_lstsize(pipeline);
	head = pipeline;
	pipeline_loop(pipeline, fd, head);
	return (head);
}
