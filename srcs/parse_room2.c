/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_room2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 15:54:36 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 17:53:35 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int			free_str(char *str, char *str2, int ret)
{
	ft_strdel(&str);
	if (str2)
		ft_strdel(&str2);
	return (ret);
}

int			check_int(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] && tmp[i] != ' ')
		i++;
	if (i > 11)
		return (0);
	if (ft_atoi(tmp) > 2147483647 || ft_atoi(tmp) < 0)
		return (0);
	return (1);
}

static void	free_parse(t_parse *new)
{
	t_parse *tmp;
	t_parse *tmp2;

	tmp = new;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->line)
			ft_strdel(&tmp->line);
		if (tmp->name)
			ft_strdel(&tmp->name);
		free(tmp);
		tmp = tmp2;
	}
	new = NULL;
}

int			all_ok(t_save *save, t_parse *new, t_room **room)
{
	int	ok;

	ok = 0;
	if (save->ok_start == 2 || save->ok_end == 2 || save->nb_link > 0)
	{
		*room = create_room(new, save);
		ok = 1;
	}
	free_parse(new);
	return (ok);
}
