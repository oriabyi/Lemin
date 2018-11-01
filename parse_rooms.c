/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:43:55 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/01 15:43:56 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				fill_common_room(t_lemin *lemin, char **split)
{
	t_room		*temp;

	if (!lemin->rooms)
	{
		if (!(lemin->rooms = (t_room *)malloc(sizeof(t_room))))
			return (MEMORY_ERROR);
		*lemin->rooms = (t_room){NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL};
	}
	else
	{
		temp = lemin->rooms;
		lemin->rooms = lemin->rooms->next;
		if (!(lemin->rooms = (t_room *)malloc(sizeof(t_room))))
			return (MEMORY_ERROR);
		*lemin->rooms = (t_room){NULL, 0, 0, 0, 0, 0, NULL, temp, NULL};
		lemin->rooms->prev->next = lemin->rooms;
	}
	if (!lemin->rooms->name)
	{
		*lemin->rooms = (t_room){ft_strdup(split[0]), ft_atoi(split[1]),
			ft_atoi(split[2]), lemin->num_rooms++, 0, 0,
			NULL, lemin->rooms->prev, NULL};
	}
	return (OK);
}

int				fill_rooms(t_lemin *lemin, char **line)
{
	int			code;
	char		**split;

	split = ft_strsplit(*line, ' ', 1);
	if (!split || !(split[0]) || !(split[1]) ||
		!(split[2]) || !are_nums(split[1]) || !are_nums(split[2]))
	{
		free_char_matrix(split);
		return (free_str_return_int(line, WRONG_DATA_ROOMS));
	}
	else if (split[0][0] == 'L')
	{
		free_char_matrix(split);
		return (free_str_return_int(line, FIRST_CHR_ROOM_L));
	}
	else if (get_room_by_name(lemin, split[0]))
	{
		free_char_matrix(split);
		return (free_str_return_int(line, MULTI__ROOMS));
	}
	code = fill_common_room(lemin, split);
	free_char_matrix(split);
	return (code);
}

int				fill_start_end_rooms(t_lemin *lemin,
						char **split, int code, char *line)
{
	if (lemin->start && lemin->end)
		return (MULTI_MAIN_ROOMS);
	if (get_room_by_name(lemin, line))
		return (MULTI__ROOMS);
	if (code && !lemin->start)
	{
		if (!(lemin->start = (t_room *)malloc(sizeof(t_room))))
			return (MEMORY_ERROR);
		*lemin->start = (t_room){ft_strdup(split[0]), ft_atoi(split[1]),
			ft_atoi(split[2]), lemin->num_rooms++, 0, 0, NULL, NULL, NULL};
		fill_rooms(lemin, &line);
		lemin->rooms->num = lemin->start->num;
	}
	else if (!lemin->end)
	{
		if (!(lemin->end = (t_room *)malloc(sizeof(t_room))))
			return (MEMORY_ERROR);
		*lemin->end = (t_room){ft_strdup(split[0]), ft_atoi(split[1]),
			ft_atoi(split[2]), lemin->num_rooms++, 0, 0, NULL, NULL, NULL};
		fill_rooms(lemin, &line);
		lemin->rooms->num = lemin->end->num;
	}
	lemin->num_rooms--;
	return (OK);
}

int				fill_mroom(t_lemin *lemin, int code, char **ret)
{
	int			ret_code;
	char		*line;
	char		**split;

	gnl(0, &line);
	split = ft_strsplit(line, ' ', 1);
	if (!split || !(split[0]) || !(split[1]) || !(split[2])
		|| !are_nums(split[1]) || !are_nums(split[2]))
	{
		free_char_matrix(split);
		return (free_str_return_int(&line, WRONG_DATA_ROOMS));
	}
	else if (split[0][0] == 'L')
	{
		free_char_matrix(split);
		return (free_str_return_int(&line, FIRST_CHR_ROOM_L));
	}
	ret_code = fill_start_end_rooms(lemin, split, code, line);
	*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
	free_char_matrix(split);
	return (ret_code);
}

int				get_rooms(t_lemin *lemin, char **ret)
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
		else if ((!ft_strcmp((line), "##start") || !ft_strcmp((line), "##end"))
			&& (code = fill_mroom(lemin, !ft_strcmp((line), "##start") ? 1 : 0,
					ret)))
			return (code);
		else if (ft_strchr(line, '-'))
		{
			fill_links(lemin, line);
			*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
			break ;
		}
		else if (*line != '#' && (code = fill_rooms(lemin, &line)))
			return (free_str_return_int(&line, code));
		*ret = (line) ? ft_multjoinfr(5, NULL, *ret, NULL, line, "\n") : *ret;
	}
	return (lemin->rooms ? code : WRONG_DATA_ROOMS);
}
