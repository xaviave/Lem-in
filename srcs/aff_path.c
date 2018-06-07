/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aff_path.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/05 13:07:51 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/07 15:09:47 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int		path_size(int *path, int max)
{
	int	room;

	room = 0;
	while (path[room] != -1 && room < max)
		room++;
	return (room);
}

int		still_ant(t_save *save)
{
	int	i;
	int	j;
	int	size;

	i = -1;
	while (++i < save->nb_path)
	{
		size = 0;
		while (save->path[i][size] != -1 && size < save->nb_room)
			size++;
		j = -1;
		while (++j < size - 1)
			if (save->path[i][j])
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
	save->nb_fill = save->nb_path;
	while (++i < save->nb_path)
	{
		size = 0;
		while (save->path[i][size] != -1 && size < save->nb_room)
			size++;
		if (!(save->fill[i] = (int *)malloc(sizeof(int) * size - 1)))
			return ;
		save->fill[i] = tab_filler(0, size - 1);
	}
	save->nb_fill = 1;
}

void	aff_path(t_save *save, t_room *room)
{
	int	i;
	int	space;

	i = -1;
	ft_printf("%s\n", save->line);
	init_fill(save);
	ft_printf(GRN"start aff:	nb_ant = %d	||	nb_path = %d\n"RESET, save->nb_ant, save->nb_path);
	while (still_ant(save) || save->nb_fill < save->nb_ant + 1)
	{
		space = 0;
		aff_ant(save, room, space);
		ft_printf("\n");
	}
	ft_printf(GRN"end aff\n"RESET);
	i = -1;
	while (++i < save->nb_path)
		free(save->path[i]);
	save->nb_fill = save->nb_path;
	free_room(room, save->nb_room);
	free_save(save);
}
