/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:52:22 by fbouanan          #+#    #+#             */
/*   Updated: 2022/06/04 15:52:23 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 1024);
	if (!pwd)
		return ;
	printf("%s\n", pwd);
	//ft_putendl(pwd);
	free(pwd);
}
