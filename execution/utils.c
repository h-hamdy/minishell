/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:11:11 by fbouanan          #+#    #+#             */
/*   Updated: 2022/09/06 22:53:19 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putendl(char *s)
{
	int	i;

	i = 0;
	if (s)
		ft_putstr(s);
	write (1, "\n", 1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	diff;
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	diff = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] != s2[i])
	{
		diff = s1[i] - s2[i];
		return (diff);
	}
	return (0);
}

int	rest_open_files(t_list *pipeline, int i)
{
	if (((t_cmd *)pipeline->content)->type[i] == 1)
	{
		infile_procces(pipeline, i);
	}
	else if (((t_cmd *)pipeline->content)->type[i] == 2)
	{
		outfile_procces(pipeline, i);
	}
	else if (((t_cmd *)pipeline->content)->type[i] == 3)
	{
		append_hand(pipeline, i);
	}
	return (0);
}

int	open_files(t_list *pipeline, int *fd)
{
	int	i;

	(void)fd;
	if (((t_cmd *)pipeline->content)->red)
	{
		i = 0;

			while (((t_cmd *)pipeline->content)->red[i])
			{
				rest_open_files(pipeline, i);
				if (g_v.perm)
					break ;
				i++;
			}
	}
	else if (!((t_cmd *)pipeline->content)->arg)
	{
		close(fd[1]);
		return (0);
	}
	return (0);
}

void	for_unset(t_list *pipeline, int k)
{
	g_v.exit_code = 1;
	ft_putstr_fd("unset: \'", 2);
	ft_putstr_fd(((t_cmd *)pipeline->content)->arg[k], 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}
