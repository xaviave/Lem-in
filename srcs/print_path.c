/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_path.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/07 15:09:33 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/07 15:14:31 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static void	send_first_ant(t_save *save, t_room *room, int space, int path)
{
	int		i;
	int		max;

	i = -1;
	if (save->nb_ant < path_size(save->path[path], save->nb_room)
			|| save->nb_path == 1)
		max = save->nb_ant;
	else
		max = 1;
	while (++i < max)
	{
		if (save->nb_fill < save->nb_ant + 1)
		{
			save->fill[path][1] = save->nb_fill;
			(!space) ? 0 : ft_printf(" ");
			space = 1;
			ft_printf("L%d-%s", save->nb_fill, room[save->path[path][1]].name);
			save->nb_fill++;
		}
	}
}

void		aff_ant(t_save *save, t_room *room, int space)
{
	int		i;

	i = -1;
	while (++i < save->nb_path)
	{
		//faire avancer les fourmis
		send_first_ant(save, room, space, i);
	}
}			
