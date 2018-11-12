/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:43:55 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:25:43 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				fill_start_end_rooms(t_lemin *lemin,
					char **split, int code, char *line)
{
	if (lemin->start && lemin->end)
		return (MULTI_MAIN_ROOMS);
	if (get_room_by_name(lemin, split[0]))
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

	while (gnl(0, &line) && line && *line == '#')
	{
		*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
	}
	split = ft_strsplit(line, ' ', 1);
	ret_code = bad_line_for_rooms(split, line);
	if (ret_code)
	{
		free_char_matrix(split);
		return (free_str_return_int(&line, ret_code));
	}
	ret_code = fill_start_end_rooms(lemin, split, code, line);
	*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
	free_char_matrix(split);
	return (ret_code);
}

int				get_rooms_help(t_lemin *lemin,
					char **ret, char **line, int *code)
{
	if (*code == LINK)
	{
		*code = fill_links(lemin, *line);
		*ret = ft_multjoinfr(5, NULL, *ret, NULL, *line, "\n");
		return (*code);
	}
	else if (*code == ROOM)
	{
		if ((*code = fill_rooms(lemin, line)))
			return (free_str_return_int(line, *code));
	}
	else if (*code == MAIN_ROOM)
	{
		*ret = ft_multjoinfr(4, NULL, *ret, *line, "\n");
		if ((*code = fill_mroom(lemin, !ft_strcmp((*line), "##start") ? 1 : 0, ret)))
			return (free_str_return_int(line, *code));
		ft_strdel(line);
	}
	else if (*code == WRONG_DATA)
		return (free_str_return_int(line, WRONG_DATA));
	return (-1);
}

int				get_rooms(t_lemin *lemin, char **ret)
{
	char		*line;
	int			code;

	while ((code = gnl(0, &line)))
	{
		code = what_the_line_is(&line);
		if (code == COMMENT || code == COMMAND)
		{
			*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
			continue ;
		}
		if (code == BAD_LINE)
			break ;
		else if (code == ANT)
			return (free_str_return_int(&line, WRONG_PLACE_ANTS));
		else if ((code = get_rooms_help(lemin, ret, &line, &code)) != -1)
			return (code);
		if (line)
			*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
	}
	(code == 0) ? free(line) : 0;
	return (lemin->rooms && lemin->start && lemin->end ? OK : WRONG_DATA_ROOMS);
}
