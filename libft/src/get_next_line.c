/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:11:47 by cuzureau          #+#    #+#             */
/*   Updated: 2017/03/08 15:38:37 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_save_rest(int leak, char *s, int start, int len)
{
	char		*dst;

	if (!s || !(dst = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	ft_strncpy(dst, &s[start], len);
	dst[len] = '\0';
	if (leak == 1)
		free(s);
	return (dst);
}

static int		ft_save_line(int j, char *buf, char **line)
{
	int			i;

	i = 0;
	if (!(*line = ft_save_rest(1, *line, 0, ft_strlen(*line) + BUFF_SIZE)))
		return (-1);
	while (buf[i] && buf[i] != MARK)
		line[0][j++] = buf[i++];
	return (buf[i] == MARK ? (i + 1) : -1);
}

static int		get_next_line_first(int *j, char **line, char **sv)
{
	int			i;

	if ((i = ft_save_line(0, *sv, line)) >= 0)
		return ((*sv = ft_save_rest(1, *sv, i, ft_strlen(*sv) - i)) ? 1 : -1);
	*line = *sv;
	*j = ft_strlen(*sv);
	*sv = NULL;
	return (0);
}

static int		get_next_line_second(int *j, char **line, char **sv, int fd)
{
	int			i;
	int			ret;
	char		buf[BUFF_SIZE + 1];

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if ((i = ft_save_line(*j, buf, line)) >= 0)
			return ((*sv = ft_save_rest(0, buf, i, BUFF_SIZE - i)) ? 1 : -1);
		*j = *j + BUFF_SIZE;
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	int			j;
	int			tmp;
	static char *sv = NULL;

	j = 0;
	tmp = 0;
	if (fd < 0 || !line || !(*line = ft_strnew(1)))
		return (-1);
	if (sv != NULL)
	{
		tmp = get_next_line_first(&j, line, &sv);
		if (tmp == -1)
			return (-1);
		if (tmp == 1)
			return (1);
	}
	tmp = get_next_line_second(&j, line, &sv, fd);
	if (tmp == -1)
		return (-1);
	if (tmp == 1)
		return (1);
	return ((ft_strlen(*line) > 0) ? 1 : 0);
}
