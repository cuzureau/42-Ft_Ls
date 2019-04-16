/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:35:14 by cuzureau          #+#    #+#             */
/*   Updated: 2016/12/24 10:20:18 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen((char *)s);
	if ((char)c == '\0')
		return ((char *)s + i);
	i--;
	while (s[i])
	{
		if ((char)s[i] == c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
