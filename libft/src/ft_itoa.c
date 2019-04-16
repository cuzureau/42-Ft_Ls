/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 10:48:23 by cuzureau          #+#    #+#             */
/*   Updated: 2017/06/13 12:13:49 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*dst;
	int		i;
	int		tmp;

	tmp = n;
	i = ft_nummalloc(tmp) - 1;
	if (n == -2147483648)
		return (dst = ft_strdup("-2147483648"));
	if (!(dst = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	if (n == 0)
		dst[0] = 48;
	if (n < 0)
	{
		dst[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		dst[i] = (n % 10 + '0');
		n = n / 10;
		i--;
	}
	dst[ft_nummalloc(tmp)] = '\0';
	return (dst);
}
