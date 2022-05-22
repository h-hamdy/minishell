/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:06:20 by hhamdy            #+#    #+#             */
/*   Updated: 2022/05/22 16:42:00 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parcing_function(void)
{
	char	*line;

	while (1)
	{
		line = readline("\033[0;36mMinishell$ \033[0;37m");
		add_history(line);
		error_handling(line);
	}
}
