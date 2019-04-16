/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:19:01 by cuzureau          #+#    #+#             */
/*   Updated: 2016/11/30 10:13:01 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size > 0)
	{
		while (dst[i] && i < size)
			i++;
		while (src[j] && (i + j) < (size - 1))
		{
			dst[i + j] = src[j];
			j++;
		}
		if (i < size)
			dst[i + j] = 0;
	}
	return (i + ft_strlen(src));
}
