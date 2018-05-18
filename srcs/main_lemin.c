/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_lemin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/20 15:51:56 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/18 13:27:23 by xamartin    ###    #+. /#+    ###.fr     */
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
	save->line = NULL;
}

int			main(void)
{
	t_save	save;
	t_room	*room;
	t_parse *new;

	new = NULL;
	init_save(&save);
	if (!(room = (t_room *)malloc(sizeof(t_room) * 101)))
		return (ft_printf("ERROR\n"));
	if (!parse_lemin(&save, new, &room))
	{
		/*
		   free room
		   free save
		   */
		return (ft_printf(RED"ERROR"RESET));
	}
	/*
	int i = -1;
	int j;
	while (++i < save.nb_room)
	{
		j = -1;
		ft_printf("\n nom = %s | id = %d | nb_link = %d | x = %d | y = %d | link name = ", 
				room[i].name, room[i].id, room[i].nb_link, room[i].x, room[i].y);
		while (++j < room[i].nb_link)
			ft_printf("%d // ", room[i].link_id[j]);
	}
	*/
	ft_printf(GRN"OK"RESET);
	return (0);
}
