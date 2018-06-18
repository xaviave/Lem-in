/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_path.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/07 15:09:33 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 09:57:22 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	send_first_ant(t_save *save, t_room *room, int *space, int p)
{
	int		i;
	int		ret;
	int		max;

	i = -1;
	ret = 0;
	if (2 == path_size(save->path[p], save->nb_room) && save->nb_path == 1)
	{
		max = save->nb_ant;
		ret = 1;
	}
	else
		max = 1;
	while (++i < max)
	{
		if (save->nb_fill < save->nb_ant + 1)
		{
			save->fill[p][1] = save->nb_fill;
			(!(*space)) ? 0 : ft_printf(" ");
			*space = 1;
			ft_printf("L%d-%s", save->nb_fill, room[save->path[p][1]].name);
			save->nb_fill++;
		}
	}
	return (ret);
}

void		push_ant(t_save *save, t_room *room, int *space, int path)
{
	int		i;
	int		j;

	j = path_size(save->path[path], save->nb_room);
	i = j;
	while (--j && j)
	{
		if (j - 1 && save->fill[path][j - 1])
		{
			save->fill[path][j] = save->fill[path][j - 1];
			save->fill[path][j - 1] = 0;
			(!(*space)) ? 0 : ft_printf(" ");
			*space = 1;
			ft_printf("L%d-%s", save->fill[path][j],
					room[save->path[path][j]].name);
		}
	}
	save->fill[path][i - 1] = 0;
}

int			aff_ant(t_save *save, t_room *room, int j)
{
	int		i;
	int		space;

	space = 0;
	i = -1;
	while (++i < save->nb_path)
		if (j && path_size(save->path[i], save->nb_room))
			push_ant(save, room, &space, i);
	i = -1;
	while (++i < save->nb_path)
		if (send_first_ant(save, room, &space, i))
			return (0);
	return (1);
}
