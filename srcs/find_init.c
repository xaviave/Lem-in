/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_init.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 14:36:09 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 16:53:37 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void		free_tab(t_save *save)
{
	int		i;

	i = -1;
	while (++i < save->nb_fill)
		free(save->fill[i]);
	free(save->fill);
	save->nb_fill = 0;
}

t_path		*remove_first(t_path *path)
{
	t_path	*new;

	new = NULL;
	if (path->next)
		new = path->next;
	free(path);
	return (new);

}

int			*tab_filler(int fill, int length)
{
	int		i;
	int		*tab;

	i = -1;
	if (!(tab = (int *)malloc(sizeof(int ) * length)))
		return (NULL);
	while (++i < length)
		tab[i] = fill;
	return (tab);
}

void		free_path(t_path *path)
{
	t_path	*tmp;
	t_path	*tmp2;

	tmp = path;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	path = NULL;
}

int			*copy_tab(int *tab, int size)
{
	int		i;
	int		*copy;

	i = -1;
	copy = tab_filler(-1, size);
	while (++i < size)
		copy[i] = tab[i];
	return (copy);
}
