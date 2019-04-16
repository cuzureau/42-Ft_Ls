/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:16:40 by cuzureau          #+#    #+#             */
/*   Updated: 2016/11/30 11:43:47 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(const char *s)
{
	int		i;
	int		k;
	int		j;
	char	*dst;
	int		p;

	i = 0;
	p = 0;
	if (!s)
		return (NULL);
	k = ft_strlen(s);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	while (s[k - 1] == ' ' || s[k - 1] == '\t' || s[k - 1] == '\n')
		k--;
	j = k - i;
	if (j < 0)
		j = 0;
	if (!(dst = (char*)malloc(sizeof(char) * j + 1)))
		return (NULL);
	while (s[i] != '\0' && p < j)
		dst[p++] = s[i++];
	dst[p] = '\0';
	return (dst);
}
