/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_path.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/22 13:33:49 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 09:56:26 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	init_verif(t_save *save, int ok)
{
	int		i;
	int		j;

	i = -1;
	if (ok)
		free(save->verif);
	save->verif = tab_filler(0, save->nb_room);
	if (ok)
	{
		i = -1;
		while (++i < save->nb_path)
		{
			j = -1;
			while (++j < save->nb_room && save->path[i][j] != -1)
				save->verif[save->path[i][j]] = 1;
		}
	}
	save->verif[save->start_id] = 0;
	save->verif[save->end_id] = 0;
}

static void	init_start_end(t_save *save, t_room *room)
{
	int		i;

	i = -1;
	while (++i < save->nb_room)
		if (!ft_strcmp(room[i].name, save->start))
			save->start_id = i;
	i = -1;
	while (++i < save->nb_room)
		if (!ft_strcmp(room[i].name, save->end))
			save->end_id = i;
	save->nb_fill = 0;
	init_verif(save, 0);
	save->nb_path = 0;
}

static int	fill_path(t_path *path, t_room *room, t_save *save)
{
	int		i;
	int		gene;

	i = -1;
	gene = 0;
	if (!(save->fill = (int **)malloc(sizeof(int *) * save->nb_link)))
		return (0);
	path = add_link(save->start_id, save, room);
	save->nb_gene++;
	while (!save->verif[save->end_id] && path)
	{
		next_gene(path, room, save);
		path = remove_first(path);
		if (++i == gene)
		{
			gene = find_nb_gene(path, save->nb_gene);
			save->nb_gene++;
			i = -1;
		}
	}
	free_path(path);
	if (good_path(save))
		return (1);
	return (0);
}

int			find_path(t_save *save, t_room *room)
{
	int		i;
	t_path	*path;

	i = -1;
	if (!room[save->start_id].nb_link)
		return (0);
	if (!(save->path = (int **)malloc(sizeof(int *) * save->nb_link)))
		return (0);
	init_start_end(save, room);
	while (++i < save->nb_link)
	{
		path = NULL;
		save->nb_gene = 0;
		if (!fill_path(path, room, save))
			break ;
		save->nb_path++;
		init_verif(save, 1);
		free_tab(save);
	}
	return (0);
}
