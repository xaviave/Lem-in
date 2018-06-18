/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aff_path.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/05 13:07:51 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 09:56:08 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			path_size(int *path, int max)
{
	int		room;

	room = 0;
	while (path[room] != -1 && room < max)
		room++;
	return (room);
}

int			still_ant(t_save *save)
{
	int		i;
	int		j;
	int		size;

	i = -1;
	while (++i < save->nb_path)
	{
		size = path_size(save->path[i], save->nb_room);
		j = -1;
		while (++j < size)
			if (save->fill[i][j])
				return (1);
	}
	return (0);
}

static void	init_fill(t_save *save)
{
	int		i;
	int		size;

	i = -1;
	if (!(save->fill = (int **)malloc(sizeof(int *) * save->nb_path)))
		return ;
	while (++i < save->nb_path)
	{
		size = 0;
		while (save->path[i][size] != -1 && size < save->nb_room)
			size++;
		save->fill[i] = tab_filler(0, size - 1);
	}
	save->nb_fill = 1;
}

void		aff_path(t_save *save, t_room *room)
{
	int		j;

	j = -1;
	ft_printf("%s\n", save->line);
	init_fill(save);
	while ((still_ant(save) || save->nb_fill < save->nb_ant + 1))
	{
		if (!aff_ant(save, room, ++j))
		{
			ft_printf("\n");
			break ;
		}
		ft_printf("\n");
	}
	j = -1;
	while (++j < save->nb_path)
		free(save->path[j]);
	save->nb_fill = save->nb_path;
	free_room(room, save->nb_room);
	free_save(save);
}
