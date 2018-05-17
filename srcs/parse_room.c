/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_room.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/24 14:48:47 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 15:19:36 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int			check_double_name(char *line, t_parse *new, int id)
{
	int		i;
	char	*tmp;
	t_parse	*list;

	i = 0;
	while (line[i] != ' ')
		i++;
	tmp = ft_strsub(line, 0, i);
	list = new;
	while (list)
	{
		while (!list->name && list)
			list = list->next;
		if (list->id == id)
		{
			ft_strdel(&tmp);
			return (1);
		}
		if (!ft_strcmp(tmp, list->name))
		{
			ft_strdel(&tmp);
			return (0);
		}
		list = list->next;
	}
	ft_strdel(&tmp);
	return (1);
}

int		check_name(char *line, t_parse *new, int id)
{
	int	i;

	i = -1;
	while (line[++i] != ' ')
		if (line[i] == 'L' || line[i] == '-')
			return (0);
	if (!check_double_name(line, new, id))
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

int		parse_room(char *line, t_save *save, t_parse *new, t_parse *list)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	list->name = ft_strsub(line, 0, i);
	if (check_name(line, new, list->id) && check_room(line))
	{
		list->room = 1;
		save->nb_room++;
	}
	else
		return (0);
	return (1);
}
