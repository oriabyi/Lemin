/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:05:59 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/01 15:06:00 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char			*get_name_link(char *line)
{
	size_t		i;
	char		*ret;

	i = 0;
	while ((line)[i] && (line)[i] != '-')
		i++;
	ret = ft_strsub(line, 0, i);
	return (ret);
}

int				is_oppo(t_room *room, int num)
{
	t_oppo		*head;

	head = room->oppo;
	while (head)
	{
		if (head->room && head->room->num == num)
			return (1);
		head = head->next;
	}
	return (0);
}

int				add_oppos(t_lemin *lemin, char *first, char *second)
{
	t_room		*temp_first;
	t_room		*temp_second;

	if (!(temp_first = get_room_by_name(lemin, first)))
		return (NO_ROOM);
	if (!(temp_second = get_room_by_name(lemin, second)))
		return (NO_ROOM);
	if (is_oppo(temp_first, temp_second->num) == 0)
		return (add_oppo(temp_first, temp_second));
	return (OK);
}

int				fill_links(t_lemin *lemin, char *line)
{
	int			code;
	char		*first;
	char		*second;

	first = get_name_link(line);
	second = get_name_link(line + ft_strlen(first) + 1);
	code = add_oppos(lemin, first, second);
	free(first);
	free(second);
	return (code);
}

int				get_links(t_lemin *lemin, char **ret)
{
	char		*line;
	int			code;

	code = OK;
	while (gnl(0, &line))
	{
		if (check_line(line) == 1)
			break ;
		else if (are_nums(line))
			return (free_str_return_int(&line, WRONG_PLACE_ANTS));
		else if (!ft_strcmp((line), "##start") || !ft_strcmp((line), "##end"))
			return (free_str_return_int(&line, WRONG_PLACE_ROOMS));
		else if (ft_strpos(line, '-') > 0)
		{
			if ((code = fill_links(lemin, line)))
				return (free_str_return_int(&line, code));
		}
		else if (*line != '#')
			return (free_str_return_int(&line, WRONG_PLACE_ROOMS));
		if (line)
			*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
	}
//	ft_strdel(&line);
	return (lemin->start && lemin->end ? code : NO_LINKS);
}
