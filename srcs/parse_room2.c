/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_room2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 15:54:36 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/18 14:35:35 by xamartin    ###    #+. /#+    ###.fr     */
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

static void	free_parse(t_parse *new, t_save *save)
{
	int		i;
	t_parse *tmp;
	t_parse *tmp2;

	i = -1;
	tmp2 = new;
	while (tmp2 && ++i <= save->nb_line)
	{
		tmp = tmp2->next;
		ft_strdel(&tmp2->line);
		if (tmp2->name)
			ft_strdel(&tmp2->name);
		free(tmp2);
		tmp2 = tmp;
	}
	new = NULL;
}

int			all_ok(t_save *save, t_parse *new, t_room **room)
{
	int	ok;

	ok = 0;
	if (save->ok_start == 2 && save->ok_end == 2 && save->nb_link > 0)
	{
		*room = create_room(new, save);
		ok = 1;
	}
	free_parse(new, save);
	return (ok);
}
