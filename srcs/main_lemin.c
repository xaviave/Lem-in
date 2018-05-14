/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_lemin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/20 15:51:56 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/07 23:39:19 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static void	init_save(t_save *save)
{
	save->nb_room = 0;
	save->nb_ant = 0;
	save->nb_link = 0;
	save->ok_start = 0;
	save->ok_end = 0;
	save->start = NULL;
	save->end = NULL;
	save->name = NULL;
}

int			main(void)
{
	t_save	save;
	t_room	*room;

	init_save(&save);
	if (!(room = (t_room *)malloc(sizeof(t_room) * 101)))
		return (ft_printf("ERROR\n"));
	if (!parse_lemin(&save, room))
		return (0);
	//free_room(room);
}
