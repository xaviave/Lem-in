/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_path.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/22 13:33:49 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/29 14:11:45 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static void	init_start_end(t_save *save, t_room *room)
{
	int	i;

	i = -1;
	while (++i < save->nb_room)
		if (!ft_strcmp(room[i].name, save->start))
			save->start_id = i;
	i = -1;
	while (++i < save->nb_room)
		if (!ft_strcmp(room[i].name, save->end))
			save->end_id = i;
}

static t_path	*add_link(int nu)
{		
	t_path		*new;

	if (!(new = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	new->id = nu;
	ft_printf("add link  %d\n", nu);
	new->next = NULL;
	return (new);
}

static void	next_gene(t_path *path, t_room *room, int *verif)
{
	int		j;
	t_path	*new;

	j = -1;
	new = path;
	while (new->next)
		new = new->next;
	ft_printf("next_gene id = %d\n", new->id);
	while (++j < room[path->id].nb_link)
	{
		if (!verif[room[path->id].link_id[j]])
		{
			new->next = add_link(room[path->id].link_id[j]);
			new = new->next;
		}
	}
}

void		fill_tab(t_path *path, int *verif)
{
	t_path	*new;

	new = path;
	while (new)
	{
		verif[new->id] = 1;
		new = new->next;
	}
}

t_path *remove_first(t_path *path)
{
	t_path *new;

	new = NULL;
	if (path->next)
		new = path->next;
	free(path);
	return (new);

}

static void	fill_path(t_path *path, t_room *room, t_save *save)
{
	int		i;
	int		*verif;
	//	t_path *new;

	i = save->start_id;
	if (!(verif = (int *)malloc(sizeof(int) * save->nb_room)))
		return ;
	while (++i < save->nb_room)
		verif[i] = 0;
	path = add_link(save->start_id);
	next_gene(path, room, verif);
	fill_tab(path, verif);
	while (!verif[save->end_id])
	{
		path = remove_first(path);
		next_gene(path, room, verif);
		fill_tab(path, verif);
	}
}

int	find_path(t_save *save, t_room *room)
{
	int		i;
	t_path	*path;

	i = -1;
	init_start_end(save, room);
	if (!room[save->start_id].nb_link)
		return (0);
	path = NULL;
	fill_path(path, room, save);
	return (0);
}
