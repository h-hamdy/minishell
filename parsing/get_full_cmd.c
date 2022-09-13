/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:34:46 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/11 16:53:34 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_condition(char c)
{
	return (c && !is_quote(c) && !is_metachar(c) && !ft_isspace(c));
}

int	get_items(char *line, t_cmd *data, char **env)
{
	int	count_red;
	int	count_her;
	int	count_arg;

	count_red = count_redirection(line);
	count_her = count_herdoc(line);
	count_arg = count_args(line);
	if (!count_her && !count_arg && !count_red)
		return (0);
	if (count_arg)
	{
		allocate_fill_arg(line, data, count_arg);
		data->cmd_path = find_path(data->arg[0], env);
	}
	if (count_red)
		allocate_fill_red(line, data, count_red);
	if (count_her)
		allocate_fill_her(line, data, count_her);
	return (1);
}

void	initialize_struct(t_cmd *data)
{
	data->cmd_path = 0;
	data->arg = 0;
	data->red = 0;
	data->type = 0;
	data->limiter = 0;
	data->in = 0;
	data->out = 0;
}

t_list	*get_full_cmd(char **s_line, char **env)
{
	int		col;
	t_cmd	*data;
	t_list	*head;
	char	*dollar;

	col = -1;
	head = NULL;
	dollar = NULL;
	while (s_line[++col])
	{
		g_v.cmp_exit = col;
		data = malloc(sizeof(t_cmd));
		initialize_struct(data);
		dollar = expand_dollar(s_line[col]);
		if (!get_items(dollar, data, env))
		{
			if (dollar)
				free(dollar);
			return (NULL);
		}
		if (dollar)
			free(dollar);
		ft_lstadd_back(&head, ft_lstnew(data));
	}
	return (head);
}
