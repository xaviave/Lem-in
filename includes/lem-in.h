/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem-in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 09:15:59 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 18:31:15 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef _LEM_IN_H
# define _LEM_IN_H

# include "../libft/libft.h"

typedef struct	s_save
{
	char		*start;
	char		*end;
	char		**name;
	int			nb_ant;
	int			nb_room;
	int			nb_link;
	int			begin_link;
}				t_save;

typedef struct	s_room
{
	char		*name;
	int			id;
	int			*link_id;//missing
	int			nb_link;
	int			x;
	int			y;
	char		*ant_name;
}				t_room;

void			free_room(t_room **room, t_save *save);
void			free_save(t_save *save);
int				parse_lemin(t_save *save, t_room **room);
int				check_room(char *line);
int				check_name(char **line, t_save *save);
int				check_room_name(t_room **room ,t_save *save);
void			init_room(char *line, t_room *room, int size);
int				parse_all_room(char **line, t_save *save, t_room *room);
int				parse_all_link(char **line, t_save *save, t_room *room);
int				check_link(char *line, t_save *save);
void			free_char(char **line);
char			**realloc_char(char **line, int size);
int				*realloc_int(int *tab, int size);

#endif