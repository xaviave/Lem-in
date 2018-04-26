/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_link.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/24 14:48:40 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 18:01:03 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static void	fill_link(char *here, char *link, t_room *room, t_save *save)
{
	int		i;
	int		nb;

	i = -1;
	while (++i < save->nb_room)
		if (!ft_strcmp(save->name[i], here))
			nb = i;
	i = -1;
	while (++i < save->nb_room)
		if (!ft_strcmp(save->name[i], link))
			break ;
	if (!room[nb].nb_link)
	{
		if (!(room[nb].link_id = (int *)malloc(sizeof(int) * 1)))
			return ;
		room[nb].link_id[0] = room[i].id;
		room[nb].nb_link++;
	}
	else
	{
		room[nb].link_id = realloc_int(room[nb].link_id, room[nb].nb_link);
		room[nb].link_id[room[nb].nb_link] = room[i].id;
		room[nb].nb_link++;
	}
}

static void	init_link(char *line, t_room *room, t_save *save)
{
	int		i;
	int		good;
	char	*first;
	char	*second;

	i = 0;
	good = 0;
	while (line[i] && line[i] != '-')
		i++;
	first = ft_strsub(line, 0, i);
	second = ft_strsub(line, i + 1, ft_strlen(line));
	fill_link(first, second, room, save);
	fill_link(second, first, room, save);
	ft_strdel(&first);
	ft_strdel(&second);
}

int			check_link(char *line, t_save *save)
{
	int		i;
	int		good;
	char	*str;

	i = 0;
	good = 0;
	while (line[i] && line[i] != '-')
		i++;
	str = ft_strsub(line, 0, i);
	i = -1;
	while (++i < save->nb_room)
		if (!ft_strcmp(str, save->name[i]))
			good++;
	ft_strdel(&str);
	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	str = ft_strsub(line, i + 1, ft_strlen(line));
	i = -1;
	while (++i < save->nb_room)
		if (!ft_strcmp(str, save->name[i]))
			good++;
	ft_strdel(&str);
	if (good != 2)
		return (0);
	return (1);
}

int			parse_all_link(char **line, t_save *save, t_room *room)
{
	int		i;
	int		link;

	link = 0;
	i = save->begin_link - 1;
	while (line[++i])
	{
		while (line[i][0] == '#')
		{
			if (!line[i + 1] && line[i][0])
				break ;
				i++;
		}
		if (!check_link(line[i], save))
			break ;
		else
		{
			init_link(line[i], room, save);
			link++;
		}
	}
	save->nb_link = link;
	return (1);
}
