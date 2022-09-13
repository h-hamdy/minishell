/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 06:47:01 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/01 07:28:20 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_struct(t_list *pipiline)
{
	if (((t_cmd *)pipiline->content)->limiter)
		d_free(((t_cmd *)pipiline->content)->limiter);
	if (((t_cmd *)pipiline->content)->red)
		d_free(((t_cmd *)pipiline->content)->red);
	if ((((t_cmd *)pipiline->content)->arg))
		d_free(((t_cmd *)pipiline->content)->arg);
	if (((t_cmd *)pipiline->content)->type)
		free(((t_cmd *)pipiline->content)->type);
	if (((t_cmd *)pipiline->content)->cmd_path)
		free(((t_cmd *)pipiline->content)->cmd_path);
	free(((t_cmd *)pipiline->content));
}

void	d_free(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
	str = NULL;
}

int	count_d_pointer(char **ptr)
{
	int	index;

	index = 0;
	if (!ptr)
		return (0);
	while (ptr[index])
		index++;
	return (index);
}
