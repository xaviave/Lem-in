/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_init.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/23 13:44:10 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/15 16:42:45 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void		free_char(char **line)
{
	int		i;

	i = -1;
	while (line[++i])
		ft_strdel(&(line[i]));
	free(line);
}

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
	int		i;

	i = -1;
	while (++i < save->nb_room)
		ft_strdel(&save->name[i]);
	free(save->name);
	ft_strdel(&save->start);
	ft_strdel(&save->start);
}

void		free_room(t_room **room, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		ft_strdel(&room[i]->name);
		ft_strdel(&room[i]->ant_name);
	}
	free(*room);
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
	new->link = 1;
	new->link = 0;
	return (new);
}
