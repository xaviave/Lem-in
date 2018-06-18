/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_lemin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/20 15:51:56 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 09:56:52 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	init_save(t_save *save)
{
	save->nb_room = 0;
	save->nb_ant = 0;
	save->nb_link = 0;
	save->ok_start = 0;
	save->ok_end = 0;
	save->start_id = 0;
	save->end_id = 0;
	save->start = NULL;
	save->end = NULL;
	save->line = NULL;
	save->path = NULL;
	save->verif = NULL;
	save->fill = NULL;
}

int			main(void)
{
	t_save	save;
	t_room	*room;
	t_parse *new;

	new = NULL;
	init_save(&save);
	if (parse_lemin(&save, new, &room) != 1)
	{
		free_save(&save);
		return (ft_printf(RED"ERROR"RESET));
	}
	find_path(&save, room);
	if (save.nb_path)
	{
		if (save.fill && save.nb_fill)
			free_tab(&save);
		aff_path(&save, room);
		return (0);
	}
	free_room(room, save.nb_room);
	free_save(&save);
	return (ft_printf(RED"ERROR"RESET));
}
