/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 15:38:04 by cuzureau          #+#    #+#             */
/*   Updated: 2017/10/27 17:02:18 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char				*ft_format(char *line_l, char **long_l, int *max)
{
	short int		i;
	int				j;

	i = 0;
	j = 0;
	while (i < 8)
	{
		ft_strncpy(&line_l[j], long_l[i], ft_strlen(long_l[i]));
		j = (i == 0 ? max[0] + 2 + max[1] - ft_strlen(long_l[1]) : j);
		j += (i == 1 || i == 4 ? 1 + ft_strlen(long_l[i]) : 0);
		j += (i == 2 ? max[2] + 2 : 0);
		j += (i == 3 ? max[3] + 2 + max[4] - ft_strlen(long_l[4]) : 0);
		j += (i == 5 ? max[5] + 1 : 0);
		j += (i == 6 ? ft_strlen(long_l[6]) : 0);
		if (i == 7 && long_l[7][0] != '\0')
		{
			ft_strcpy(&line_l[j], " -> ");
			ft_strncpy(&line_l[j + 4], long_l[7], ft_strlen(long_l[7]));
			j += 4 + ft_strlen(long_l[7]);
		}
		i++;
	}
	line_l[j] = '\0';
	return (line_l);
}

void				ft_padding(char *line_l, char **long_l, int *max)
{
	short int		i;
	int				total_max;

	i = 0;
	total_max = 0;
	while (i < 8)
		total_max += max[i++];
	ft_memset(line_l, ' ', (total_max + 19));
	line_l = ft_format(line_l, long_l, max);
	free(long_l[0]);
	free(long_l[1]);
	free(long_l[2]);
	free(long_l[3]);
	free(long_l[4]);
	free(long_l[5]);
	free(long_l[6]);
	free(long_l[7]);
	free(long_l);
}
