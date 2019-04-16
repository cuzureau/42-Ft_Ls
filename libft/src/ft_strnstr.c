/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:47:49 by cuzureau          #+#    #+#             */
/*   Updated: 2016/11/24 11:17:04 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!little[i])
		return ((char *)big);
	while (big[i])
	{
		while (big[i + j] == little[j] && (i + j) < len)
		{
			j++;
			if (j == ft_strlen(little))
				return ((char *)&big[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
