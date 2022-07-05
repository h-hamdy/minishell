/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:34:46 by hhamdy            #+#    #+#             */
/*   Updated: 2022/07/04 17:05:04 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	check_red_type(char *line, int index)
{
	if (line[index] == '>' && line[index + 1] == '>')
		return (3);
	if (line[index] == '<')
		return (1);
	return (2);
}

void	allocate_arg(char *line, t_cmd *data, int count_arg)
{
	int index;
	int token;
	int count;
	int sign;

	index = 0;
	token = 0;
	sign = 0;

	int row;
	int col = 0;
	data->arg = (char **)malloc(sizeof(char *) * (count_arg + 1));
	while (line[index])
	{
		row = 0;
		index = ignore_space(line, index);
		if (line[index] == '<' || line[index] == '>')
			index = skip_redirecition(line, index);
		index = ignore_space(line, index);
		if (line[index] && line[index] != '<' && line[index] != '>')
		{
			index = ignore_space(line, index);
			count = ft_count_word(line, index);
			data->arg[token] = (char *)malloc(sizeof(char) * (count + 1));
			while (1)
			{
				if (line[index] == '"' || line[index] == '\'')
				{
					sign = line[index];
					index++;
					while (line[index] && line[index] != sign)
					{
						data->arg[col][row] = line[index];
						index++;
						row++;
					}
					index++;
				}
				if (line[index] && line[index] != '"' && line[index] != '\'' && line[index] != '<' && line[index] != '>' && line[index] != ' ')
				{
					while (line[index] && line[index] != '"' && line[index] != '\'' && line[index] != '<' && line[index] != '>' && line[index] != ' ')
					{
						data->arg[col][row] = line[index];
						index++;
						row++;
					}
				}
				if (line[index] != '"' && line[index] != '\'')
					break ;
			}
			data->arg[col][row] = '\0';
			col++;
			token++;
		}
	}
	data->arg[token] = NULL;
}

void	allocate_fill_her(char *line, t_cmd *data, int count_her)
{
	int	index;
	int count;
	int token;
	int flag;
	int col;
	int row;
	char sign;
	
	index = 0;
	token = 0;
	flag = 0;
	col = 0;
	data->limiter = (char **)malloc(sizeof(char *) * (count_her + 1));
	while (line[index])
	{
		row = 0;
		if (line[index] == '<' && line[index + 1] == '<')
		{
			index += 2;
			index = ignore_space(line, index);
			count = ft_count_word(line, index);
			data->limiter[token] = (char *)malloc(sizeof(char *) * count + 1);
			while (1)
			{
				if (line[index] == '"' || line[index] == '\'')
				{
					sign = line[index];
					index++;
					while (line[index] && line[index] != sign)
					{
						data->limiter[col][row] = line[index];
						index++;
						row++;
					}
					index++;
				}
				if (line[index] && line[index] != '"' && line[index] != '\'' && line[index] != '<' && line[index] != '>' && line[index] != ' ')
				{
					while (line[index] && line[index] != '"' && line[index] != '\'' && line[index] != '<' && line[index] != '>' && line[index] != ' ')
					{
						data->limiter[col][row] = line[index];
						index++;
						row++;
					}
				}
				if (!line[index] || (line[index] != '"' && line[index] != '\''))
					break ;
			}
			data->limiter[col][row] = '\0';
			col++;
			token++;
		}
		else
			index++;
	}
	data->limiter[token] = NULL;
}

void	allocate_red(char *line, t_cmd *data, int count_red)
{
	int	index;
	int	c_type;
	int count;
	int	token;
	int	flag;

	index = 0;
	token = 0;
	flag = 0;
	c_type = 0;
	data->red = (char **)malloc(sizeof(char *) * (count_red + 1));
	data->type = (int *)malloc(sizeof(int) * (count_red + 1));
	while (line[index])
	{
		flag = 0;
		if (line[index] == '<' && line[index + 1] == '<')
		{
			index += 2;
			index = ignore_space(line, index);
			if (line[index] == '"' || line[index] == '\'')
				index = skip_word(line, index, 1);
			else
				index = skip_word(line, index, 0);
		}
		if ((line[index] == '>' && line[index + 1] == '>')
			|| (line[index] == '>' || line[index] == '<'))
		{
			data->type[c_type] = check_red_type(line, index);
			c_type++;
			index++;
			if (line[index] == '>')
				index++;
			index = ignore_space(line, index);
			count = ft_count_word(line, index);
			data->red[token] = (char *)malloc(sizeof(char) * (count + 1));
			if (!data->red[token])
				return ((void)ft_free(data->red, token - 1));
			token++;
			if (line[index] == '"' || line[index] == '\'')
				flag = 1;
			index = skip_word(line, index, flag);
		}
		else if (line[index])
			index++;
	}
	data->red[token] = NULL;
}

void	fill_red(char *line, t_cmd *data)
{
	int index;
	int	col;
	int row;

	index = 0;
	col = 0;
	while (line[index])
	{
		if (line[index] == '<' && line[index + 1] == '<')
			index += 2;
		if (line[index] == '<' || line[index] == '>')
		{
			row = 0;
			index++;
			if (line[index] == '>')
				index++;
			index = ignore_space(line , index);
			if (line[index] == '"' || line[index] == '\'')
			{
				if (line[index] == '"')
				{
					index++;
					while (line[index] && line[index] != '"')
					{
						data->red[col][row] = line[index];
						index++;
						row++;
					}
				}
				else
				{
					index++;
					while (line[index] && line[index] != '\'')
					{
						data->red[col][row] = line[index];
						index++;
						row++;
					}
				}	
			}
			else if (line[index] && line[index] != ' ' && line[index] != '<' && line[index] != '>')
			{
				while (line[index] && line[index] != ' ' && line[index] != '<' && line[index] != '>' && line[index] != '"' && line[index] != '\'')
				{
					data->red[col][row] = line[index];
					index++;
					row++;
				}
			}
			data->red[col][row] = '\0';
			index--;
			col++;
		}
		index++;
	}
	data->red[col] = NULL;
}


int	get_items(char *line, t_cmd *data, char **env)
{
	// int count_red;
	int	count_her;
	int	count_arg;

	// count_red = count_redirection(line);
	count_her = count_herdoc(line);
	count_arg = count_args(line);
	// printf("arg = %d, her = %d\n", count_arg, count_her);
	// if (!count_her && !count_arg && !count_red)
	// 	return (0);
	if (count_arg)
	{
		allocate_arg(line, data, count_arg);
		data->cmd_path = find_path(data->arg[0], env);
	}
	// if (count_red)
	// {
	// 	allocate_red(line, data, count_red);
		// fill_red(line, data);
	// }
	if (count_her)
		allocate_fill_her(line, data, count_her);
	return (1);
}

void	initialize_struct(t_cmd *data)
{
	data->cmd = 0;
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
	int col;
	t_cmd *data;
	t_list *head;

	col = 0;
	head = NULL;
	while (s_line[col])
	{
		data = malloc(sizeof(t_cmd));
		initialize_struct(data);
		if (!get_items(s_line[col], data, env))
			return (NULL);
		ft_lstadd_back(&head, ft_lstnew(data));
		col++;
	}
	return (head);
}