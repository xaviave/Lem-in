/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_lemin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/07 19:00:24 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/14 15:15:05 by xamartin    ###    #+. /#+    ###.fr     */
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

static int	check_hashtag(char *line, t_save *save, t_room *room)
{
	int		i;

	i = -1;
	if (save->ok_start == 1)
	{
		if (check_room(line))
		{
			save->ok_start = 2;
			init_room(line, room, save->nb_room);
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
			init_room(line, room, save->nb_room);
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

static int	check_all(char *line, t_save *save, t_room *room)
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
			save->nb_link == 0 && check_hashtag(line, save, room))
		return (1);
	else if (save->nb_link == 0 && parse_room(line, save, room))
		return (1);
	else if (parse_link(line, save, room))
		return (1);
	return (0);
}

int			parse_lemin(t_save *save, t_room *room)
{
	int		i;
	char	*final;
	char	*tmp;
	char	**line;

	i = -1;
	final = ft_strdup("");
	while (ft_gnl(0, &tmp))
	{
		if (++i == 0 && just_nu(tmp) && check_int(tmp))
			save->nb_ant = ft_atoi(tmp);
		else if (i == 0)
			return (ft_printf(RED"ERROR"RESET));
		else if (i < 1 || !check_all(tmp, save, room))
			break ;
		final = ft_strjoinf1(final, tmp);
		ft_strdel(&tmp);
		final = ft_strjoinf1(final, "|");
	}
	if (save->ok_start == 2 && save->ok_end == 2 && save->nb_link > 0)
		ft_printf(GRN"OK\n"RESET);
	else
		return (ft_printf(RED"ERROR"RESET));
	return (1);
	i = -1;
	while (++i < save->nb_room)
		ft_printf("name = %s, x = %d, y = %d, nb_link = %d\n", room[i].name, room[i].x, room[i].y, room[i].nb_link);
	line = ft_strsplit(final, '|');
	ft_strdel(&final);
	free_char(line);
	/*
	   ft_printf(GRN"OK"RESET);
	   free_save(save);
	   while (1)
	   ;
	   */
	return (1);
}
