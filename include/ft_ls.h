/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:12:58 by cuzureau          #+#    #+#             */
/*   Updated: 2017/10/29 21:17:18 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;

	char			**long_list;
	char			*line_list;
	unsigned int	time;
	long			nanosec;
	char			*name;
	char			*link;
	char			*print;
	char			isdir;

}					t_btree;

typedef struct		s_dir
{
	char			**name_dir;
	char			**wrong_dir;
	char			**no_dir;
	int				*opt;
	int				*max_len;

	char			*path;
	char			*path_dir;
	void			*dir;
	void			*dir2;
	int				munki;
	struct dirent	*file;
	struct stat		infos;
	struct stat		tmp_infos;
	struct passwd	*user;
	struct group	*group;
	time_t			*tloc;
	blkcnt_t		blocksize;
	char			empty;

	int				first_result;
	t_btree			*node;
	t_btree			*bad_param;
	t_btree			*file_param;
	t_btree			*param;
	char			*very_first;

}					t_dir;

void				ft_free(t_btree *node);
void				ft_create_path(char *path, char *first, char *second);
void				ft_init(t_dir *d);
void				ft_final_free(t_dir *d);
void				ft_print_munki(t_dir *d);

char				*ft_format(char *line_l, char **long_l, int *max);
void				ft_padding(char *line_l, char **long_l, int *max);

void				ft_illegal(t_dir *d, char *option);
void				ft_sort_param(t_dir *d, char **av, int i);
void				ft_print_param(t_dir *d, t_btree *tree);
void				ft_check_args(t_dir *d, int ac, char **av);

void				ft_recurs(t_btree *tree, t_dir *d, char *current);
void				ft_recurs_rev(t_btree *tree, t_dir *d, char *current);
int					ft_list(t_dir *d, char *current);
void				ft_display_dir(t_btree *tree, t_dir *d);
int					main(int ac, char **av);

char				*ft_permissions(t_dir *d, char *perm);
char				*ft_modification_time(t_dir *d);
char				*ft_devices(t_dir *d);
void				ft_count_len(t_dir *d, char **long_l);
char				**ft_long_listing(t_dir *d, char *param);

void				ft_print_tree(t_btree *tree, t_dir *d);
void				ft_print_tree_rev(t_btree *tree, t_dir *d);
void				ft_print_error(t_dir *d, char *current, char *name);
void				ft_print(t_dir *d, char *current);

t_btree				*ft_create_node(t_dir *d, char *param);
void				ft_by_name(t_btree **root, t_dir *d, char *name);
void				ft_by_date(t_btree **root, t_dir *d, char *name);
int					ft_create_tree(t_dir *d, char *current);

#endif
