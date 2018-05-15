/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_link.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/24 14:48:40 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/15 17:43:36 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem-in.h"

/*
   static void	fill_link(char *here, char *link, t_room *room, t_save *save)
   {
   int		i;
   int		nb;

   i = -1;
   while (++i < save->nb_room)
   if (!ft_strcmp(room[i].name, here))
   nb = i;
   i = -1;
   while (++i < save->nb_room)
   if (!ft_strcmp(room[i].name, link))
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
   */

int			check_link(char *line, t_parse *new, int id)
{
	int		i;
	int		good;
	char	*str;
	char	*str2;
	t_parse	*list;

	i = 0;
	good = 0;
	while (line[i] && line[i] != '-')
		i++;
	str = ft_strsub(line, 0, i);
	str2 = ft_strsub(line, i + 1, ft_strlen(line));
	list = new;
	while (list)
	{
		while ((!list->link1 || !list->link2) && list)
			list = list->next;
		if (list->id == id)
			return (1);
		good += (!ft_strcmp(str, list->link1) ? 1 : 0);
		good += (!ft_strcmp(str2, list->link2) ? 1 : 0);
		list = list->next;
	}
	ft_strdel(&str);
	ft_strdel(&str2);
	return (good == 2 ? 1 : 0);
}

int			parse_link(char *line, t_save *save, t_parse *new, t_parse *list)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	list->link1 = ft_strsub(line, 0, i);
	list->link2= ft_strsub(line, i + 1, ft_strlen(line));
	if (!ft_strcmp(list->link1, list->link2))
		return (0);
	if (!check_link(line, new, list->id))
		return (0);
	save->nb_link += 2;
	list->link = 1;
	return (1);
}
