/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:51:48 by fbouanan          #+#    #+#             */
/*   Updated: 2022/07/08 18:37:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_list *pipeline, char **env)
{
	int	i;
	// int	j;
	// int	flag;
	(void)env;

	i = 1;
	// printf("****here\n");

	while (((t_cmd*)pipeline->content)->arg[i])
		printf("|%s|\n", ((t_cmd*)pipeline->content)->arg[i++]);

	// while (((t_cmd*)pipeline->content)->arg[i] && ((t_cmd*)pipeline->content)->arg[i][0] == '-')
	// {
	// 	printf("here\n");
	// 	j = 1;
	// 	while (((t_cmd*)pipeline->content)->arg[i][j] == 'n')
	// 		j++;
	// 	if (((t_cmd*)pipeline->content)->arg[i][j] != '\0')
	// 		break ;
	// 	i++;
	// }
	// printf("-->%s\n", ((t_cmd*)pipeline->content)->arg[i]);
	// flag = 0;
	// if (i > 1)
	// 	flag = 1;
	// while (((t_cmd*)pipeline->content)->arg[i])
	// {
	// 	while (((t_cmd*)pipeline->content)->arg[i][k])
	// 	{
	// 		if (((t_cmd*)pipeline->content)->arg[i][k] == '$')
	// 			handel_echo(((t_cmd*)pipeline->content)->arg[i], env);
	// 		k++;
	// 	}
	// 	printf("%s", ((t_cmd*)pipeline->content)->arg[i]);
	// 	i++;
	// 	if (((t_cmd*)pipeline->content)->arg[i])
	// 		printf(" ");
	// }
	// if (flag == 0)
	// 	printf("\n");
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}
