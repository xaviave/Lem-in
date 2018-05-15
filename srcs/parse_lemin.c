/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_lemin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/07 19:00:24 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/15 16:56:38 by xamartin    ###    #+. /#+    ###.fr     */
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

static int	check_hashtag(char *line, t_save *save, t_parse *list)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	list->name = ft_strsub(line, 0, i);
	if (save->ok_start == 1)
	{
		if (check_room(line))
		{
			save->ok_start = 2;
			list->room = 1;
			save->nb_room++;
		}
		else
			return (0);
	}
	else if(save->ok_end == 1)
	{
		if (check_room(line))
		{
			save->ok_end = 2;
			list->room = 1;
			save->nb_room++;
		}
		else
			return (0);
	}
	return (1);
}


int			check_int(char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i] && tmp[i] != ' ')
		i++;
	if (i > 11)
		return (0);
	if (ft_atoi(tmp) > 2147483647 || ft_atoi(tmp) < 0)
		return (0);
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
			save->nb_link == 0 && check_hashtag(line, save, list))
		return (1);
	else if (save->nb_link == 0 && parse_room(line, save, new, list))
		return (1);
	else if (parse_link(line, save, new, list))
		return (1);
	return (0);
}

int			parse_lemin(t_save *save, t_room *room)
{
	int		i;
	char	*final;
	char	*tmp;
	t_parse	*list;
	t_parse	*new;

	i = -1;
	final = ft_strdup("");
	while (ft_gnl(0, &tmp))
	{
		if (++i == 0)
		{
			if (just_nu(tmp) && check_int(tmp))
				save->nb_ant = ft_atoi(tmp);
			else
				return (ft_printf(RED"ERROR"RESET));
			new = new_parse(tmp, i);
			list = new;
		}
		else if (list && i)
		{
			list->next = new_parse(tmp, i);
			if (!check_all(tmp, save, list, new))
				break ;
			list = list->next;
		}
		ft_strdel(&tmp);
	}
	if (save->ok_start == 2 && save->ok_end == 2 && save->nb_link > 0)
	{
		ft_printf(GRN"OK\n"RESET);
	}
	else
		return (ft_printf(RED"ERROR"RESET));
	return (1);
	while (new)
	{
		ft_printf("%s | ", new->line);
		new = new->next;
	}
	return (1);








	i = -1;
	while (++i < save->nb_room)
		ft_printf("name = %s, x = %d, y = %d, nb_link = %d\n", room[i].name, room[i].x, room[i].y, room[i].nb_link);
	ft_strdel(&final);
	/*
	   ft_printf(GRN"OK"RESET);
	   free_save(save);
	   while (1)
	   ;
	   */
	return (1);
}
