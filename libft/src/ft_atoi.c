/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 19:18:20 by cuzureau          #+#    #+#             */
/*   Updated: 2016/12/23 11:37:01 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		neg;
	int		res;

	i = 0;
	res = 0;
	neg = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == \
			'\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i + 1] == '+' || str[i + 1] == '-')
			return (res);
		else
		{
			if (str[i] == '-')
				neg = 1;
			i++;
		}
	}
	while (str[i] > 47 && str[i] < 58)
		res = res * 10 + str[i++] - 48;
	return ((neg == 1) ? -res : res);
}
