/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_room2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 15:54:36 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 09:57:16 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

	i = 0;
	tmp2 = new;
	while (tmp2 && i <= save->nb_line)
	{
		if (!tmp2)
			break ;
		tmp = tmp2->next;
		if (tmp2->line)
			ft_strdel(&tmp2->line);
		if (tmp2->name)
			ft_strdel(&tmp2->name);
		if (tmp2->link1)
			ft_strdel(&tmp2->link1);
		if (tmp2->link2)
			ft_strdel(&(tmp2->link2));
		free(tmp2);
		if (tmp)
			tmp2 = tmp;
		i++;
	}
	new = NULL;
}

int			all_ok(t_save *save, t_parse *new, t_room **room, int line)
{
	int	ok;

	ok = 0;
	save->nb_line = line;
	if (save->ok_start == 2 && save->ok_end == 2 && save->nb_link > 0)
	{
		*room = create_room(new, save);
		ok = 1;
	}
	free_parse(new, save);
	return (ok);
}
