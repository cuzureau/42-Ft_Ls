/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 18:39:10 by cuzureau          #+#    #+#             */
/*   Updated: 2016/12/23 21:09:09 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*new;

	new = malloc(sizeof(t_list));
	new->content = malloc(sizeof(content));
	if (!new || !new->content)
		return (NULL);
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		new->content = malloc(sizeof(new->content_size));
		if (!new->content)
			return (NULL);
		ft_memcpy(new->content, (void *)content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
