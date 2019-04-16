/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 11:34:26 by cuzureau          #+#    #+#             */
/*   Updated: 2017/10/29 20:32:03 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_btree				*ft_create_node(t_dir *d, char *param)
{
	t_btree			*node;

	node = ft_memalloc(sizeof(t_btree));
	node->name = ft_strdup(param);
	node->isdir = '0';
	if (S_ISDIR(d->infos.st_mode) &&
		!ft_strequ(node->name, ".") && !ft_strequ(node->name, ".."))
		node->isdir = 'd';
	if (d->opt[2] == 1 ||
			(!ft_strequ(node->name, ".") && !ft_strequ(node->name, "..")))
		d->empty = 'f';
	d->opt[0] == 1 ? (node->long_list = ft_long_listing(d, param)) : 0;
	node->time = d->infos.st_mtime;
	node->nanosec = d->infos.st_mtimespec.tv_nsec;
	if (S_ISREG(d->infos.st_mode || S_ISLNK(d->infos.st_mode)))
		node->print = ft_strdup(node->name);
	if (!d->infos.st_mode)
	{
		node->print = ft_strnew(ft_strlen(param) + 60);
		ft_strcpy(node->print, "ls: ");
		ft_strcpy(&node->print[ft_strlen(node->print)], param);
		ft_strcpy(&node->print[ft_strlen(node->print)],
				": No such file or directory\n");
	}
	return (node);
}

void				ft_by_name(t_btree **root, t_dir *d, char *name)
{
	if (*root == NULL)
	{
		*root = ft_create_node(d, name);
		return ;
	}
	if (ft_strcmp(name, (*root)->name) < 0)
		ft_by_name(&(*root)->left, d, name);
	else
		ft_by_name(&(*root)->right, d, name);
}

void				ft_by_date(t_btree **root, t_dir *d, char *name)
{
	if (*root == NULL)
	{
		*root = ft_create_node(d, name);
		return ;
	}
	if (d->infos.st_mtime > (*root)->time)
		ft_by_date(&(*root)->left, d, name);
	else if (d->infos.st_mtime < (*root)->time)
		ft_by_date(&(*root)->right, d, name);
	else
	{
		if (d->infos.st_mtimespec.tv_nsec > (*root)->nanosec)
			ft_by_date(&(*root)->left, d, name);
		else if (d->infos.st_mtimespec.tv_nsec < (*root)->nanosec)
			ft_by_date(&(*root)->right, d, name);
		else
		{
			if (ft_strcmp(name, (*root)->name) <= 0)
				ft_by_date(&(*root)->left, d, name);
			else
				ft_by_date(&(*root)->right, d, name);
		}
	}
}

int					ft_create_tree(t_dir *d, char *current)
{
	if (!(d->dir = opendir(current)))
		return (-1);
	while ((d->file = readdir(d->dir)) != NULL)
	{
		ft_create_path(d->path, current, d->file->d_name);
		if (lstat(d->path, &d->infos) == -1)
			stat(d->path, &d->infos);
		if (ft_strstr(d->path, "munki") && ft_strequ(d->file->d_name, "."))
		{
			if (!(d->dir2 = opendir(d->path)))
			{
				d->munki = 1;
				return (-1);
			}
			if (closedir(d->dir2) == -1)
				return (-1);
		}
		if (ft_strequ(d->file->d_name, ".") || ft_strequ(d->file->d_name, "..")
				|| d->file->d_name[0] != '.' ||
				(d->file->d_name[0] == '.' && d->opt[2] == 1))
			d->opt[4] == 1 ? ft_by_date(&d->node, d, d->file->d_name) :
				ft_by_name(&d->node, d, d->file->d_name);
	}
	return (closedir(d->dir) == -1 || !d->node ? -1 : 0);
}
