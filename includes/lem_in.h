/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem-in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 09:15:59 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 09:58:10 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef _LEM_IN_H
# define _LEM_IN_H

# include "../libft/libft.h"

typedef struct		s_parse
{
	char			*line;
	char			*name;
	char			*link1;
	char			*link2;
	int				id;
	int				room;
	int				link;
	struct s_parse	*next;
}					t_parse;

typedef struct		s_path
{
	int				id;
	int				gene;
	struct s_path	*next;
}					t_path;

typedef struct		s_save
{
	char			*start;
	int				start_id;
	char			*end;
	int				end_id;
	char			*line;
	int				ok_start;
	int				ok_end;
	int				nb_ant;
	int				nb_room;
	int				nb_link;
	int				nb_line;
	int				nb_gene;
	int				gene;
	int				start_ok;
	int				end_ok;
	int				nb_path;
	int				nb_fill;
	int				*verif;
	int				**fill;
	int				**path;
}					t_save;

typedef struct		s_room
{
	char			*name;
	int				id;
	int				*link_id;
	int				nb_link;
	int				x;
	int				y;
	int				ant;
}					t_room;

void				free_save(t_save *save);
void				free_room(t_room *room, int size);
int					free_str(char *str, char *str2, int ret);
int					*realloc_int(int *tab, int size);
t_parse				*new_parse(char *str, int id);
t_room				*create_room(t_parse *new, t_save *save);
int					check_int(char *tmp);
int					check_room(char *line);
int					check_room_name(t_room *room, t_save *save);
int					check_link(char *line, t_parse *new, int id);
int					all_ok(t_save *save, t_parse *new, t_room **room, int line);
void				init_room(char *line, t_room *room, int pos);
void				init_link(t_parse *list, t_room *room, t_save *save);
int					parse_lemin(t_save *save, t_parse *new, t_room **room);
int					parse_room(char *line, t_save *save, t_parse *new,
		t_parse *list);
int					parse_link(char *line, t_save *save, t_parse *new,
		t_parse *list);
int					find_path(t_save *save, t_room *room);
int					*tab_filler(int fill, int length);
int					prev_id(int id, t_room *room, t_save *save);
void				create_new_path(t_save *save, t_room *room, int id);
void				fill_tab(t_path *path, t_save *save, t_room *room);
t_path				*add_link(int id, t_save *save, t_room *room);
t_path				*remove_first(t_path *path);
void				free_path(t_path *path);
void				free_tab(t_save *save);
int					*copy_tab(int *tab, int size);
int					good_path(t_save *save);
int					next_gene(t_path *path, t_room *room, t_save *save);
int					find_nb_gene(t_path *path, int gene);
int					tabcmp(int nu, t_save *save);
void				aff_path(t_save *save, t_room *room);
int					aff_ant(t_save *save, t_room *room, int j);
int					path_size(int *path, int max);

#endif
