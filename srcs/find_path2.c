/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_path2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 16:15:36 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 13:24:26 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int			find_link(int id, t_room *room, int *verif)
{
	int		i;
	int		link;

	i = -1;
	link = 0;
	while (++i < room[id].nb_link)
	{
		if (!verif[room[i].link_id[i]])
		{
			verif[room[i].link_id[i]] = 1;
			link++;
		}
	}
	return (link);
}

int			prev_id(int id, t_room *room, t_save *save)
{
	int		i;
	int		j;

	i = -1;
	while (++i < save->nb_fill)
	{
		j = -1;
		while (++j < room[id].nb_link)
			if (save->fill[i][save->nb_gene - 1] == room[id].link_id[j])
				return (i);
	}
	return (-1);
}

void		create_new_path(t_save *save, t_room *room, int id)
{
	int		i;
	int		tmp;

	if (!save->nb_gene && !save->nb_fill)
	{
		save->fill[0] = tab_filler(-1, save->nb_room);
		save->fill[0][0] = save->start_id;
	}
	else
	{
		i = -1;
		tmp = prev_id(id, room, save);
		if (tmp > -1)
		{
			save->fill[save->nb_fill] = copy_tab(save->fill[tmp], save->nb_room);
			save->fill[save->nb_fill][save->nb_gene] = id;
		}
		else
			save->nb_fill--;
	}
}

int			tabcmp(int nu, t_save *save)
{
	int		i;
	int		j;
	int		ok;

	i = -1;
	ok = 0;
	while(++i < save->nb_path)
	{
		j = -1;
		while (++j < save->nb_room)
		{
			if (save->fill[nu][j] == save->path[i][j])
				ok++;
		}
		if (ok == save->nb_room)
			return (1);
	}
	return (0);
}
