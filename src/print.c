/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 11:34:26 by cuzureau          #+#    #+#             */
/*   Updated: 2017/10/29 20:03:33 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_print_tree(t_btree *tree, t_dir *d)
{
	if (tree->left)
		ft_print_tree(tree->left, d);
	if (d->opt[2] == 1 || (d->opt[2] == 0 && tree->name[0] != '.'))
	{
		if (d->opt[0] == 1)
		{
			tree->line_list = ft_strnew(PATH_MAX + NAME_MAX);
			ft_padding(tree->line_list, tree->long_list, d->max_len);
			ft_putendl(tree->line_list);
			free(tree->line_list);
		}
		else
			ft_putendl(tree->name);
	}
	if (tree->right)
		ft_print_tree(tree->right, d);
}

void				ft_print_tree_rev(t_btree *tree, t_dir *d)
{
	if (tree->right)
		ft_print_tree_rev(tree->right, d);
	if (d->opt[2] == 1 || (d->opt[2] == 0 && tree->name[0] != '.'))
	{
		if (d->opt[0] == 1)
		{
			tree->line_list = ft_strnew(PATH_MAX + NAME_MAX);
			ft_padding(tree->line_list, tree->long_list, d->max_len);
			ft_putendl(tree->line_list);
			free(tree->line_list);
		}
		else
			ft_putendl(tree->name);
	}
	if (tree->left)
		ft_print_tree_rev(tree->left, d);
}

void				ft_print_error(t_dir *d, char *current, char *name)
{
	char			*tmp;

	tmp = ft_strnew(ft_strlen(name) + 6);
	ft_strcpy(tmp, "ls: ");
	ft_strcpy(&tmp[ft_strlen(tmp)], name);
	if (errno == 2)
		perror(tmp);
	if (errno == 13)
	{
		if (d->first_result == 1)
		{
			ft_putstr("\n");
			ft_create_path(d->path, current, name);
			ft_putstr(d->path);
			ft_putstr(":\n");
		}
		d->munki == 0 ? perror(tmp) : 0;
	}
	free(tmp);
}

void				ft_print(t_dir *d, char *current)
{
	if (d->first_result == 1 || (d->opt[1] == 1 && d->first_result == 1))
	{
		if (!ft_strequ(current, d->very_first))
			ft_putstr("\n");
		ft_putstr(current);
		ft_putstr(":\n");
	}
	d->first_result = 1;
	d->very_first[0] = '\0';
	if (d->opt[0] == 1 && d->empty == 'f')
	{
		ft_putstr("total ");
		ft_putnbr(d->blocksize);
		ft_putstr("\n");
	}
	if (d->opt[3] == 0)
		ft_print_tree(d->node, d);
	else
		ft_print_tree_rev(d->node, d);
}
