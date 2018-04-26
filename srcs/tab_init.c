/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_init.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/23 13:44:10 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:18:30 by xamartin    ###    #+. /#+    ###.fr     */
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

char		**realloc_char(char **line, int size)
{
	int		i;
	char	**new;

	i = -1;
	if (!(new = (char **)(malloc(sizeof(char *) * size + 100))))
		return (NULL);
	while (++i < size)
		new[i] = ft_strdup(line[i]);
	free_char(line);
	return (new);
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

void		free_room(t_room **room, t_save *save)
{
	int		i;

	i = -1;
	while (++i < save->nb_room)
	{
		ft_strdel(&room[i]->name);
		ft_strdel(&room[i]->ant_name);
	}
	free(*room);
}
