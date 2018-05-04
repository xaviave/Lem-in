/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_room.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/24 14:48:47 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 18:31:51 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int		check_name(char **line, t_save *save)
{
	int	i;
	int	j;

	i = -1;
	while (++i < save->nb_room)
	{
		j = -1;
		if (line[i][0] == 'L')
			return (0);
		while (line[i][++j])
			if (line[i][j] == '-')
				return (0);
	}
	return (1);
}

int		check_room(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (str[i] != ' ')
		return (0);
	while (str[++i] && str[i] != ' ')
		if (!ft_isdigit(str[i]))
			return (0);
	if (str[i] != ' ')
		return (0);
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int		check_room_name(t_room **room, t_save *save)
{
	int	i;
	int	j;
	char	**room_name;

	if (!(room_name = (char **)malloc(sizeof(char *) * save->nb_room + 1)))
		return (0);
	i = -1;
	while (++i < save->nb_room)
		room_name[i] = ft_strdup((*room)[i].name);
	room_name[i] = 0;
	i = -1;
	while (++i < save->nb_room)
	{
		j = -1;
		while (++j < save->nb_room && j + 1 < save->nb_room)
		{
			if (j == i)
				j++;
			if (!ft_strcmp(room_name[j], (*room)[i].name))
			{
				free_char(room_name, save->nb_room);
				return (0);
			}
		}
	}
	save->name = room_name;
	return (1);
}

void		init_room(char *str, t_room *room, int size)
{
	int	i;
	int	j;
	char	*save;

	i = 0;
	j = 0;
	while (str[i] && str[i] != ' ')
		i++;
	save = ft_strsub(str, 0, i);
	room[size].name = ft_strdup(save);
	ft_strdel(&save);
	room[size].id = size;
	while (str[i + 1 + j] && str[i + 1 + j] != ' ')
		j++;
	save = ft_strsub(str, i + 1, j);
	room[size].x = ft_atoi(save);
	ft_strdel(&save);
	i = i + j + 2;
	j = 0;
	while (str[i + j] && str[i + j] != ' ')
		j++;
	save = ft_strsub(str, i, j);
	room[size].y = ft_atoi(save);
	ft_strdel(&save);
}

int		parse_all_room(char **line, t_save *save, t_room *room)
{
	int	i;
	int	j;
	int	rooms;

	i = 1;
	j = 1;
	rooms = 2;
	while (line[++i])
	{
		if (!ft_strcmp("", line[i]))
			return (0);
		while (line[i][0] == '#' && line[i + 1])
		{
			if (!line[i + 1] && line[i][0] == '#')
				break ;
			i++;
		}
		if (check_room(line[i]))
		{
			init_room(line[i], room, ++j);
			save->name[j] = ft_strdup(room[j].name);
			if (++rooms % 100 == 0)
				realloc_char(save->name, rooms + 100);
		}
		else
			break ;
	}
	save->begin_link = i;
	save->nb_room = rooms;
	return (1);
}
