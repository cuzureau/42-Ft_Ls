/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 11:34:26 by cuzureau          #+#    #+#             */
/*   Updated: 2017/10/29 20:10:28 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char				*ft_permissions(t_dir *d, char *perm)
{
	perm = ft_strnew(11);
	S_ISREG(d->infos.st_mode) ? (perm[0] = '-') : 0;
	S_ISDIR(d->infos.st_mode) ? (perm[0] = 'd') : 0;
	S_ISCHR(d->infos.st_mode) ? (perm[0] = 'c') : 0;
	S_ISBLK(d->infos.st_mode) ? (perm[0] = 'b') : 0;
	S_ISFIFO(d->infos.st_mode) ? (perm[0] = 'p') : 0;
	S_ISLNK(d->infos.st_mode) ? (perm[0] = 'l') : 0;
	S_ISSOCK(d->infos.st_mode) ? (perm[0] = 's') : 0;
	perm[1] = (d->infos.st_mode & S_IRUSR ? 'r' : '-');
	perm[2] = (d->infos.st_mode & S_IWUSR ? 'w' : '-');
	perm[3] = (d->infos.st_mode & S_IXUSR ? 'x' : '-');
	if (d->infos.st_mode & S_ISUID)
		perm[3] = (d->infos.st_mode & S_IXUSR ? 's' : 'S');
	perm[4] = (d->infos.st_mode & S_IRGRP ? 'r' : '-');
	perm[5] = (d->infos.st_mode & S_IWGRP ? 'w' : '-');
	perm[6] = (d->infos.st_mode & S_ISGID ? 'S' : '-');
	if (d->infos.st_mode & S_IXGRP)
		perm[6] = (d->infos.st_mode & S_ISGID ? 's' : 'x');
	perm[7] = (d->infos.st_mode & S_IROTH ? 'r' : '-');
	perm[8] = (d->infos.st_mode & S_IWOTH ? 'w' : '-');
	perm[9] = (d->infos.st_mode & S_ISVTX ? 'T' : '-');
	if (d->infos.st_mode & S_IXOTH)
		perm[9] = (d->infos.st_mode & S_ISVTX ? 't' : 'x');
	return (perm);
}

char				*ft_modification_time(t_dir *d)
{
	time_t			now;
	char			*tmp;
	char			*modif;

	now = 0;
	time(&now);
	tmp = ft_strdup(ctime(&d->infos.st_mtime));
	modif = ft_strnew(ft_strlen(tmp));
	if (d->infos.st_mtime >= 253402297200)
		modif = ft_strdup("Jan  1  10000");
	else if (d->infos.st_mtime < (now - 15778800) ||
			d->infos.st_mtime > (now + 15778800))
	{
		ft_strncpy(modif, &tmp[4], 7);
		ft_strncpy(&modif[ft_strlen(modif)], &tmp[19], 5);
	}
	else
		ft_strncpy(modif, &tmp[4], 12);
	free(tmp);
	return (modif);
}

char				*ft_devices(t_dir *d)
{
	char			*num;
	char			*tmp;

	if (S_ISCHR(d->infos.st_mode) || S_ISBLK(d->infos.st_mode))
	{
		num = ft_strnew(16);
		tmp = ft_itoa(major(d->infos.st_rdev));
		num[0] = ' ';
		ft_strcpy(&num[1], tmp);
		free(tmp);
		ft_strcpy(&num[ft_strlen(num)], ",     ");
		tmp = ft_itoa(minor(d->infos.st_rdev));
		ft_strcpy(&num[ft_strlen(num) - 1 - ft_strlen(tmp)], tmp);
		free(tmp);
	}
	else
		num = ft_itoa(d->infos.st_size);
	return (num);
}

void				ft_count_len(t_dir *d, char **long_l)
{
	short int		i;

	i = 0;
	while (i < 8)
	{
		if ((int)ft_strlen(long_l[i]) > d->max_len[i])
			d->max_len[i] = ft_strlen(long_l[i]);
		i++;
	}
}

char				**ft_long_listing(t_dir *d, char *param)
{
	int				i;
	char			**l;
	char			*perm;

	i = 0;
	perm = NULL;
	d->blocksize += d->infos.st_blocks;
	d->user = getpwuid(d->infos.st_uid);
	d->group = getgrgid(d->infos.st_gid);
	l = ft_memalloc(sizeof(char *) * 8);
	l[0] = ft_permissions(d, perm);
	l[1] = ft_itoa(d->infos.st_nlink);
	l[2] = (d->user ? ft_strdup(d->user->pw_name) : ft_itoa(d->infos.st_uid));
	l[3] = (d->group ? ft_strdup(d->group->gr_name) : ft_itoa(d->infos.st_gid));
	l[4] = ft_devices(d);
	l[5] = ft_modification_time(d);
	l[6] = (param ? ft_strdup(param) : ft_strdup(d->file->d_name));
	l[7] = ft_strnew(PATH_MAX);
	if (S_ISLNK(d->infos.st_mode))
		d->path[0] != '\0' ?
			(readlink(d->path, l[7], 1024)) : (readlink(param, l[7], 1024));
	if (d->opt[2] == 1 || (!ft_strequ(l[6], ".") && !ft_strequ(l[6], "..")))
		ft_count_len(d, l);
	return (l);
}
