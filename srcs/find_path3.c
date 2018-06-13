/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_path3.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 16:18:46 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/11 15:48:10 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int			find_nb_gene(t_path *path, int gene)
{
	int		i;
	t_path	*list;

	i = -1;
	list = path;
	while (list && list->gene == gene)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_path		*add_link(int id, t_save *save, t_room *room)
{
	t_path	*new;

	if (!(new = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	new->id = id;
	new->gene = save->nb_gene;
	new->next = NULL;
	save->verif[id] = 1;
	create_new_path(save, room, id);
	save->nb_fill++;
	return (new);
}

static void	end_start_ok(t_save *save, int id)
{
	if (id == save->start_id)
		save->start_ok++;
	if (id == save->end_id)
		save->end_ok++;
}

int			good_path(t_save *save)
{
	int		i;
	int		j;

	i = -1;
	while (++i < save->nb_fill)
	{
		j = -1;
		save->end_ok = 0;
		save->start_ok = 0;
		while (++j < save->nb_room)
		{
			end_start_ok(save, save->fill[i][j]);
			if (save->start_ok == 1 && save->end_ok == 1)
			{
				if (!tabcmp(i, save))
					save->path[save->nb_path] =
						copy_tab(save->fill[i], save->nb_room);
				else
					save->nb_path--;
				return (1);
			}
		}
	}
	return (0);
}

int			next_gene(t_path *path, t_room *room, t_save *save)
{
	int		j;
	int		nb;
	t_path	*new;

	j = -1;
	nb = 0;
	new = path;
	while (new->next)
		new = new->next;
	while (++j < room[path->id].nb_link)
	{
		if (!save->verif[room[path->id].link_id[j]])
		{
			new->next = add_link(room[path->id].link_id[j], save, room);
			nb++;
			new = new->next;
		}
	}
	return (nb);
}
