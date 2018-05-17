/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_lemin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/07 19:00:24 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 17:37:37 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static int	just_nu(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && (str[i] == '-' || str[i] == '+'))
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i == 0 && (str[i] == '-' || str[i] == '+'))
		return (0);
	return (1);
}

static int	check_hashtag(char *line, t_save *save, t_parse *list, t_parse *new)
{
	int		i;

	i = 0;
	if (save->ok_start == 1)
	{
		if (parse_room(line, save, new, list))
		{
			save->ok_start = 2;
			save->start = ft_strdup(list->name);
		}
		else
			return (0);
	}
	else if (save->ok_end == 1)
	{
		if (parse_room(line, save, new, list))
		{
			save->ok_end = 2;
			save->end = ft_strdup(list->name);
		}
		else
			return (0);
	}
	return (1);
}

static int	check_all(char *line, t_save *save, t_parse *list, t_parse *new)
{
	if (save->nb_ant < 1)
		return (0);
	if (!ft_strcmp(line, "##start") && save->ok_start == 0)
	{
		save->ok_start++;
		return (1);
	}
	else if (!ft_strcmp(line, "##end") && save->ok_end == 0)
	{
		save->ok_end++;
		return (1);
	}
	else if (line[0] == '#')
		return (1);
	else if (save->ok_end > 2 || save->ok_start > 2)
		return (0);
	else if ((save->ok_start == 1 || save->ok_end == 1) &&
			save->nb_link == 0 && check_hashtag(line, save, list, new))
		return (1);
	else if (save->nb_link == 0 && parse_room(line, save, new, list))
		return (1);
	else if (parse_link(line, save, new, list))
		return (1);
	return (0);
}

t_room		*create_room(t_parse *new, t_save *save)
{
	int		i;
	t_parse	*list;
	t_room	*room;

	i = -1;
	list = new;
	if (!(room = (t_room *)malloc(sizeof(t_room) * save->nb_room)))
		return (NULL);
	save->line = ft_strdup("");
	while (list)
	{
		if (list->room && ++i < save->nb_room)
			init_room(list->line, room, i);
		else if (list->link)
			init_link(list, room, save);
		list->line = ft_strjoin(list->line, "\n");
		save->line = ft_strjoinf1(save->line, list->line);
		list = list->next;
	}
	return (room);
}

int			parse_lemin(t_save *save, t_parse *new, t_room **room)
{
	int		i;
	char	*tmp;
	t_parse	*list;

	i = -1;
	while (ft_gnl(0, &tmp))
	{
		if (++i == 0)
		{
			if (!just_nu(tmp) || !check_int(tmp)
					|| (save->nb_ant = ft_atoi(tmp)) < 1)
				return (0);
			new = new_parse(tmp, i);
			list = new;
		}
		else if (list && i)
		{
			list->next = new_parse(tmp, i);
			list = list->next;
			if (!check_all(tmp, save, list, new))
				break ;
		}
		ft_strdel(&tmp);
	}
	return (all_ok(save, new, room));
}
