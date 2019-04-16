/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:08:27 by cuzureau          #+#    #+#             */
/*   Updated: 2017/10/29 20:10:43 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_create_path(char *path, char *first, char *second)
{
	ft_strcpy(path, first);
	if (!ft_strequ(first, "/"))
		ft_strcpy(&path[ft_strlen(path)], "/");
	ft_strcpy(&path[ft_strlen(path)], second);
}

void				ft_free(t_btree *node)
{
	if (!node)
		return ;
	if (node->left)
		ft_free(node->left);
	if (node->right)
		ft_free(node->right);
	free(node->name);
	node->name = NULL;
	free(node);
	node = NULL;
}

void				ft_init(t_dir *d)
{
	d->max_len = ft_memalloc(sizeof(int) * 8);
	d->opt = ft_memalloc(sizeof(int) * 5);
	d->path = ft_strnew(PATH_MAX);
	d->path_dir = ft_strnew(PATH_MAX);
	d->munki = 0;
	d->first_result = 0;
	d->bad_param = NULL;
	d->file_param = NULL;
	d->param = NULL;
}

void				ft_final_free(t_dir *d)
{
	free(d->very_first);
	free(d->name_dir);
	free(d->wrong_dir);
	free(d->no_dir);
	free(d->path);
	free(d->path_dir);
	free(d->file);
	free(d->max_len);
	free(d->opt);
	free(d);
}
