/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:49:50 by hhamdy            #+#    #+#             */
/*   Updated: 2021/11/17 20:11:48 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*str;

	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * ((len_s1 + len_s2) + 1));
	if (!str)
		return (NULL);
	str[0] = '\0';
	ft_strlcat(str, s1, len_s1 + 1);
	ft_strlcat(str, s2, len_s1 + len_s2 + 1);
	return (str);
}
