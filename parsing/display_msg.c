/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 06:45:03 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/01 07:21:30 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *msg)
{
	char	*str;

	g_v.exit_code = 258;
	str = ft_strjoin("Minishell: syntax error near unexpected token ", msg);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free(str);
}

void	display_msg(char *str)
{
	write (2, str, ft_strlen(str));
}

int	trow_err(int d_quote, int s_quote)
{
	if (d_quote % 2 != 0 || s_quote % 2 != 0)
	{
		g_v.exit_code = 258;
		write(2, "Minishell: syntax error near unexpected token\n", 47);
		return (0);
	}
	return (1);
}

void	raise_err(char err)
{
	g_v.exit_code = 258;
	write (2, "Minishell: syntax error near unexpected token ", 46);
	write (2, &err, 1);
	write (2, "\n", 1);
}
