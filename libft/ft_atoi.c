/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:43:58 by hhamdy            #+#    #+#             */
/*   Updated: 2022/05/21 09:27:19 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define L_MAX 9223372036854775807

int	ft_atoi(const char *str)
{
	size_t				i;
	unsigned long		n;
	int					mult;

	i = 0;
	mult = 1;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			mult *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (mult == 1 && n > (unsigned long)L_MAX)
			return (-1);
		else if (mult == -1 && n > (unsigned long)L_MAX + 1)
			return (0);
		n = n * 10 + (str[i++] - '0');
	}
	return (mult * (int )n);
}
