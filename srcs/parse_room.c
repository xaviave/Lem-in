/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_room.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/24 14:48:47 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/14 15:21:57 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int			check_double_name(char *line, t_room *room, t_save *save)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i] != ' ')
		i++;
	tmp = ft_strsub(line, 0, i);
	i = -1;
	while (++i < save->nb_room)
	{
		if (!ft_strcmp(tmp, room[i].name))
			return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

int		check_name(char *line, t_save *save, t_room *room)
{
	int	i;

	i = -1;
	while (line[++i] != ' ')
		if (line[i] == 'L' || line[i] == '-')
			return (0);
	if (!check_double_name(line, room, save))
			return (0);
	return (1);
}

int		check_room(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	if (str[i] != ' ' && str[i] != '\t')
		return (0);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!check_int(&str[i]))
		return (0);
	i--;
	while (str[++i] && str[i] != ' ' && str[i] != '\t')
		if (!ft_isdigit(str[i]))
			return (0);
	if (str[i] != ' ' && str[i] != '\t')
		return (0);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!check_int(&str[i]))
		return (0);
	i--;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void		init_room(char *str, t_room *room, int pos)
{
	int		i;
	int		j;
	char	*save;

	i = 0;
	j = 0;
	while (str[i] && str[i] != ' ')
		i++;
	save = ft_strsub(str, 0, i);
	room[pos].name = ft_strdup(save);
	ft_strdel(&save);
	room[pos].id = pos;
	while (str[i + 1 + j] && str[i + 1 + j] != ' ')
		j++;
	save = ft_strsub(str, i + 1, j);
	room[pos].x = ft_atoi(save);
	ft_strdel(&save);
	i = i + j + 2;
	j = 0;
	while (str[i + j] && str[i + j] != ' ')
		j++;
	save = ft_strsub(str, i, j);
	room[pos].y = ft_atoi(save);
	ft_strdel(&save);
}

int		parse_room(char *line, t_save *save, t_room *room)
{
	if (check_name(line, save, room) && check_room(line))
	{
		if (save->nb_room % 100 == 0)
			realloc_room(room, save->nb_room);
		init_room(line, room, save->nb_room);
		save->nb_room++;
	}
	else
		return (0);
	return (1);
}
