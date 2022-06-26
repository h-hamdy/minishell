/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:51:41 by fbouanan          #+#    #+#             */
/*   Updated: 2022/06/04 15:51:43 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_list *pipeline)
{
	char 	*path;
	int		i;

	i = 0;
	if (((t_cmd*)pipeline->content)->arg[0] == NULL)
	{
		path = ft_strdup(getenv("HOME"));
		printf("~\n");
	}
	// if (((t_cmd*)pipeline->content)->arg[1][0] == '\0')
	// 	printf("\n");
	else
		path = ft_strdup(((t_cmd*)pipeline->content)->arg[i]);
	if (chdir(path) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(path);
		return ;
	}
	free(path);
}
