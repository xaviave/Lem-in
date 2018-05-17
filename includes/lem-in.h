/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem-in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 09:15:59 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 15:31:45 by xamartin    ###    #+. /#+    ###.fr     */
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

typedef struct		s_save
{
	char			*start;
	char			*end;
	int				ok_start;
	int				ok_end;
	char			**name;
	int				nb_ant;
	int				nb_room;
	int				nb_link;
	char			*line;
}					t_save;

typedef struct		s_room
{
	char			*name;
	int				id;
	int				*link_id;
	int				nb_link;
	int				x;
	int				y;
	char			*ant_name;
}					t_room;

void				free_room(t_room **room, int size);
void				free_save(t_save *save);
int					parse_lemin(t_save *save, t_room *room);
int					check_room(char *line);
int					check_room_name(t_room *room, t_save *save);
void				init_room(char *line, t_room *room, int pos);
void				init_link(t_parse *list, t_room *room, t_save *save);
int					parse_room(char *line, t_save *save, t_parse *new, t_parse *list);
int					parse_link(char *line, t_save *save, t_parse *new, t_parse *list);
int					check_link(char *line, t_parse *new, int id);
int					check_int(char *tmp);
void				free_char(char **line);
t_parse				*new_parse(char *str, int id);
int					*realloc_int(int *tab, int size);

#include <stdio.h>

#endif
