/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:47:11 by cuzureau          #+#    #+#             */
/*   Updated: 2017/10/29 21:11:40 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_illegal(t_dir *d, char *option)
{
	int				i;
	int				dash;

	i = 0;
	dash = 0;
	while (option[i])
	{
		option[i] == '-' ? dash++ : 0;
		if (option[i] != '-' || dash >= 2)
		{
			if (option[i] != 'R' && option[i] != 'a' && option[i] != '1' &&
					option[i] != 'l' && option[i] != 'r' && option[i] != 't')
			{
				ft_putstr_fd("ls: illegal option -- ", 2);
				ft_putchar_fd((dash >= 2 ? '-' : option[i]), 2);
				ft_putstr_fd(("\nusage: ls [-Ralrt] [file ...]\n"), 2);
				ft_final_free(d);
				exit(1);
			}
		}
		i++;
	}
}

void				ft_sort_param(t_dir *d, char **av, int i)
{
	while (av[i])
	{
		if (!av[i][0])
		{
			ft_putstr_fd("ls: fts_open: No such file or directory\n", 2);
			exit(1);
		}
		if (stat(av[i], &d->infos) != 0 || d->opt[0] == 1)
			lstat(av[i], &d->infos);
		if (S_ISREG(d->infos.st_mode) || S_ISLNK(d->infos.st_mode))
		{
			d->opt[4] == 1 ? ft_by_date(&d->file_param, d, av[i]) : 0;
			d->opt[4] == 0 ? ft_by_name(&d->file_param, d, av[i]) : 0;
		}
		if (!d->infos.st_mode)
			ft_by_name(&d->bad_param, d, av[i]);
		if (S_ISDIR(d->infos.st_mode))
		{
			d->opt[4] == 1 ? ft_by_date(&d->param, d, av[i]) : 0;
			d->opt[4] == 0 ? ft_by_name(&d->param, d, av[i]) : 0;
		}
		d->infos.st_mode = 0;
		i++;
	}
}

void				ft_print_param(t_dir *d, t_btree *tree)
{
	if (tree->left)
		ft_print_param(d, tree->left);
	ft_putstr_fd(tree->print, 2);
	if (tree->right)
		ft_print_param(d, tree->right);
}

void				ft_check_first(t_btree *tree, t_dir *d)
{
	if (tree->left)
		ft_check_first(tree->left, d);
	else
		d->very_first = ft_strdup(tree->name);
}

void				ft_check_args(t_dir *d, int ac, char **av)
{
	int				i;

	i = 1;
	while (i < ac && !ft_strequ("--", av[i]) &&
			(av[i][0] == '-' && !ft_strequ("-", av[i])))
	{
		ft_illegal(d, av[i]);
		ft_strchr(av[i], 'l') ? (d->opt[0] = 1) : 0;
		ft_strchr(av[i], 'R') ? (d->opt[1] = 1) : 0;
		ft_strchr(av[i], 'a') ? (d->opt[2] = 1) : 0;
		ft_strchr(av[i], 'r') ? (d->opt[3] = 1) : 0;
		ft_strchr(av[i], 't') ? (d->opt[4] = 1) : 0;
		i++;
	}
	ft_strequ(av[i], "--") ? i++ : 0;
	i == ac ? ft_by_name(&d->param, d, ".") : 0;
	(i < ac - 1) ? d->first_result = 1 : 0;
	ft_sort_param(d, av, i);
	d->bad_param ? ft_print_param(d, d->bad_param) : 0;
	(d->file_param && d->opt[3] == 0) ? ft_print_tree(d->file_param, d) : 0;
	(d->file_param && d->opt[3] == 1) ? ft_print_tree_rev(d->file_param, d) : 0;
	(d->param && d->file_param) ? ft_putstr("\n") : 0;
	d->param ? ft_check_first(d->param, d) : 0;
}
