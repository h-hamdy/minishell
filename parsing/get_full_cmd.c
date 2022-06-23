/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:34:46 by hhamdy            #+#    #+#             */
/*   Updated: 2022/06/23 23:57:28 by hhamdy           ###   ########.fr       */
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

void	alloc_and_fill_cmd(char *line, t_cmd *data, int count_cmd)
{
	int index;
	int row;

	row = 0;
	data->cmd = (char *)malloc(sizeof(char) * (count_cmd + 1));
	index = check_cmd(line, 1);
	if (line[index] == '"' || line[index] == '\'')
	{
		if (line[index] == '"')
		{
			index++;
			while (line[index] && line[index] != '"')
			{
				data->cmd[row] = line[index];
				index++;
				row++;
			}
		}
		else
		{
			index++;
			while (line[index] && line[index] != '\'')
			{
				data->cmd[row] = line[index];
				index++;
				row++;
			}
		}
		data->cmd[row] = '\0';
	}
	else if (line[index] && line[index] != ' ' && line[index] != '<' && line[index] != '>')
	{
		while (line[index] && line[index] != '<' && line[index] != '>' && line[index] != ' ')
		{
			data->cmd[row] = line[index];
			row++;
			index++;
		}
	}
	data->cmd[row] = '\0';
}

// void	allocate_arg(char *line, t_cmd *data, int count_arg)
// {
// 	int index;
// 	int token;
// 	int count;
// 	int flag;

// 	index = 0;
// 	token = 0;
// 	flag = 0;
// 	data->arg = (char **)malloc(sizeof(char) * count_arg + 1);
// 	while (line[index])
// 	{
// 		index = ignore_space(line, index);
// 		if (line[index] == '<' || line[index] == '>')
// 			index = skip_redirecition(line, index);
// 		index = ignore_space(line, index);
// 		if (line[index] != '<' || line[index] != '>')
// 		{
// 			if (flag == 1)
// 			{
// 				count = skip_word(line, &index);
// 				data->arg[token] = (char *)malloc(sizeof(char) * count + 1);
// 				token++;
// 				index--;
// 			}
// 			else
// 			{
// 				flag = 1;
// 				skip_word(line, &index);
// 			}
// 		}
// 	}
// 	data->arg[token] = NULL;
// }

// void	fill_arg(char *line, t_cmd *data)
// {
// 	int index;
// 	int col;
// 	int row;
// 	int flag;

// 	index = 0;
// 	col = 0;
// 	flag = 0;
// 	while (line[index])
// 	{
// 		row = 0;
// 		index = ignore_space(line, index);
// 		if (line[index] == '<' || line[index] == '>')
// 			index = skip_redirecition(line, index);
// 		index = ignore_space(line, index);
// 		if (line[index] != '<' || line[index] != '>')
// 		{
// 			if (flag == 1)
// 			{
				
// 			}
// 			else
// 			{
// 				flag = 1;
// 				skip_word(line, &index);
// 			}
// 		}
// 	}
// 	data->arg[col] = NULL;
// }

void	allocate_her(char *line, t_cmd *data, int count_her)
{
	int	index;
	int count;
	int token;

	index = 0;
	token = 0;
	data->limiter = (char **)malloc(sizeof(char *) * (count_her + 1));
	while (line[index])
	{
		if (line[index] == '<' && line[index + 1] == '<')
		{
			index += 2;
			index = ignore_space(line, index);
			count = ft_count_word(line, index);
			data->limiter[token] = (char *)malloc(sizeof(char) * count + 1);
			if (!data->limiter[token])
				return ((void)ft_free(data->limiter, token - 1));
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
	int count;
	int	token;
	int	flag;

	index = 0;
	token = 0;
	flag = 0;
	data->red = (char **)malloc(sizeof(char *) * (count_red + 1));
	data->type = (int *)malloc(sizeof(int) * (count_red + 1));
	while (line[index])
	{
		if (line[index] == '<' && line[index + 1] == '<')
			index += 2;
		if ((line[index] == '>' && line[index + 1] == '>')
			|| (line[index] == '>' || line[index] == '<'))
		{
			data->type[flag] = check_red_type(line, index);
			index++;
			if (line[index] == '>')
				index++;
			index = ignore_space(line, index);
			count = ft_count_word(line, index);
			data->red[token] = (char *)malloc(sizeof(char) * (count + 1));
			if (!data->red[token])
				return ((void)ft_free(data->red, token - 1));
			token++;
			flag++;
		}
		else
			index++;
	}
	data->red[token] = NULL;
}

void	fill_her(char *line, t_cmd *data)
{
	int index;
	int	col;
	int row;

	index = 0;
	col = 0;
	while (line[index])
	{
		if (line[index] == '<' && line[index + 1] == '<')
		{
			row = 0;
			index += 2;
			index = ignore_space(line , index);
			if (line[index] == '"' || line[index] == '\'')
			{
				if (line[index] == '"')
				{
					index++;
					while (line[index] && line[index] != '"')
					{
						data->limiter[col][row] = line[index];
						index++;
						row++;
					}
				}
				else
				{
					index++;
					while (line[index] && line[index] != '\'')
					{
						data->limiter[col][row] = line[index];
						index++;
						row++;
					}
				}
			}
			else if (line[index] && line[index] != ' ' && line[index] != '<' && line[index] != '>')
			{
				while (line[index] && line[index] != ' ' && line[index] != '<' && line[index] != '>')
				{
					data->limiter[col][row] = line[index];
					index++;
					row++;
				}
			}
			data->limiter[col][row] = '\0';
			index--;
			col++;
		}
		index++;
	}
	data->limiter[col] = NULL;
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
				while (line[index] && line[index] != ' ' && line[index] != '<' && line[index] != '>')
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


int	get_items(char *line, t_cmd *data)
{
	int count_red;
	int	count_her;
	int	count_cmd;
	// int	count_arg;

	count_red = count_redirection(line);
	count_her = count_herdoc(line);
	count_cmd = check_cmd(line, 0);
	// count_arg = count_args(line);
	if (!count_red && !count_her && !count_cmd)
		return (0);
	if (count_cmd)
	{
		alloc_and_fill_cmd(line, data, count_cmd);
		// if (count_arg)
		// {
		// 	allocate_arg(line, data, count_arg);
		// 	fill_arg(line, data);
		// 	exit(1);
		// }
	}
	if (count_red)
	{
		allocate_red(line, data, count_red);
		fill_red(line, data);
	}
	if (count_her)
	{
		allocate_her(line, data, count_her);
		fill_her(line, data);
	}
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

t_list	*get_full_cmd(char **s_line)
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
		if (!get_items(s_line[col], data))
			return (NULL);
		ft_lstadd_back(&head, ft_lstnew(data));
		col++;
	}
	return (head);
}