/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:11:11 by fbouanan          #+#    #+#             */
/*   Updated: 2022/08/22 17:11:15 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
}

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
	int diff;
	int i;

	if (!s1 || !s2)
	{
		printf("--here\n");
		return(-1);
	}
	i = 0;
	diff = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] != s2[i])
	{
		diff = s1[i] - s2[i];
		return (diff);
	}
	else
		return (0);
}

void	open_files(t_list *pipeline, int *fd)
{
	int i;

	if (((t_cmd*)pipeline->content)->red)
	{
		i = 0;
		while (((t_cmd*)pipeline->content)->red[i])
		{
			if (((t_cmd*)pipeline->content)->type[i] == 1)
				infile_procces(pipeline, i);
			else if (((t_cmd*)pipeline->content)->type[i] == 2)
				outfile_procces(pipeline, i);
			else if (((t_cmd*)pipeline->content)->type[i] == 3)
				append_hand(pipeline, i);
			i++;
		}
	}
	if (!((t_cmd*)pipeline->content)->arg)
	{
		close(fd[0]);
		close(fd[1]);
		return ;
	}
}
