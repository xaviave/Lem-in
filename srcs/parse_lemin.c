/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_lemin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/20 15:11:28 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 18:00:03 by xamartin    ###    #+. /#+    ###.fr     */
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

static int	check_hashtag(char **line, t_room **room)
{
	int		i;
	int		nb;

	i = -1;
	nb = 0;
	while (line[++i])
	{
		if (!ft_strcmp(line[i], "##start"))
		{
			while (line[i] && line[i][0] == '#')
				i++;
			if (!check_room(line[i]) || (*room)[0].name || !line[i])
				return (0);
			init_room(line[i], *room, 0);
			line[i][0] = '#';
			nb++;
		}
		else if (!ft_strcmp(line[i], "##end"))
		{
			while (line[i] && line[i][0] == '#')
				i++;
			if (!check_room(line[i]) || (*room)[1].name || !line[i])
				return (0);
			init_room(line[i], *room, 1);
			line[i][0] = '#';
			nb++;
		}
	}
	if (nb != 2)
		return (0);
	return (1);
}

static int	possible(t_save *save)
{
	if (save->nb_room < 2)
		return (0);
	if (save->nb_ant < 1 || save->nb_ant > 2147483647)
		return (0);
	if (save->nb_link < 1)
		return (0);
	return (1);
}

static int	check_all(char **line, t_save *save, t_room **room)
{

	if (!check_hashtag(line, room) || !parse_all_room(line, save, *room))
		return (0);
	if (!check_name(line, save) || !check_room_name(room, save))
		return (0);
	if (!parse_all_link(line, save, *room) || !possible(save))
		return (0);
	save->start = ft_strdup((*room)[0].name);
	save->end = ft_strdup((*room)[1].name);
	/*
	ft_printf(PINK"test\n"CYN);
	int		i;
	i = -1;
	int j;
	while (++i < save->nb_room)
	{
		ft_printf("\nname : %s, x = %d, y = %d, id = %d\n", (*room)[i].name, (*room)[i].x, (*room)[i].y, (*room)[i].id);
		j = -1;
		while (++j < (*room)[i].nb_link)
			ft_printf("link = %d  |  ", (*room)[i].link_id[j]);
	}
	*/
	ft_printf(GRN"OK"RESET);
	return (1);
}

int			parse_lemin(t_save *save, t_room **room)
{
	int		i;
	char	**line;

	if (!(line = (char **)malloc(sizeof(char *) * 100)))
		return (0);
	ft_gnl(0, &(line[0]));
	i = -1;
	if (line[0] && just_nu(line[0]))
	{
		if (!(save->name = (char **)malloc(sizeof(char *) * 100)))
			return (0);
		save->nb_ant = ft_atoi(line[0]);
		ft_strdel(&(line[0]));
		while (ft_gnl(0, &(line[++i])))
		{
			if (i % 100 == 0 && i)
				line = realloc_char(line, i);
		}
		if (!check_all(line, save, room))
			ft_printf(RED"ERROR"RESET);
	}
	else
		ft_printf(RED"ERROR"RESET);
	free(save);
	free(line);
	return (1);
}
