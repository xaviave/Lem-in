/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_init.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/23 13:44:10 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 19:59:54 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int			*realloc_int(int *tab, int size)
{
	int		i;
	int		*new;

	i = -1;
	if (!(new = (int *)(malloc(sizeof(int) * size + 1))))
		return (NULL);
	while (++i < size)
		new[i] = tab[i];
	free(tab);
	return (new);
}

void		free_save(t_save *save)
{
	if (save->start)
		ft_strdel(&save->start);
	if (save->end)
		ft_strdel(&save->end);
	if (save->line)
		ft_strdel(&save->line);
	if (save->path)
		free(save->path);
	if (save->verif)
		free(save->verif);
	if (save->fill)
		free_tab(save);
}

void		free_room(t_room *room, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		if (room[i].nb_link)
			free(room[i].link_id);
		if (room[i].name)
			ft_strdel(&room[i].name);
	}
	free(room);
}

t_parse		*new_parse(char *str, int id)
{
	t_parse	*new;

	if (!(new = (t_parse *)malloc(sizeof(t_parse))))
		return (NULL);
	new->line = ft_strdup(str);
	new->name = NULL;
	new->link1 = NULL;
	new->link2 = NULL;
	new->id = id;
	new->link = 0;
	new->room = 0;
	new->next = NULL;
	return (new);
}
