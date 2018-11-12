/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms_dop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:52:56 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:25:55 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void				free_char_matrix(char **str)
{
	int				counter;

	counter = 0;
	if (!str)
		return ;
	while (str[counter])
		free(str[counter++]);
	free(str);
}

int					fill_common_room(t_lemin *lemin, char **split)
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

int					bad_line_for_rooms(char **split, char *line)
{
	if (!line || count_chars(line, ' ') != 2 || !split ||
		!(split[0]) || !(split[1]) || !(split[2]) || split[3] ||
		are_nums(split[1]) || are_nums(split[2]))
		return (WRONG_DATA_ROOMS);
	else if (split[0][0] == 'L')
		return (FIRST_CHR_ROOM_L);
	return (0);
}

int					fill_rooms(t_lemin *lemin, char **line)
{
	int				code;
	char			**split;

	split = ft_strsplit(*line, ' ', 1);
	code = bad_line_for_rooms(split, *line);
	if (code)
	{
		free_char_matrix(split);
		return (free_str_return_int(line, code));
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

int					what_the_line_is(char **line)
{
	if (check_line(line) == 1)
		return (BAD_LINE);
	else if (ft_strcmp(*line, "##start") == 0 ||
		ft_strcmp(*line, "##end") == 0)
		return (MAIN_ROOM);
	else if (**line == '#' && *(*line + 1) == '#')
		return (COMMAND);
	else if (**line == '#')
		return (COMMENT);
	else if (count_chars(*line, ' ') == 2)
		return (ROOM);
	else if (count_chars(*line, ' ') == 0 &&
		count_chars(*line, '-') > 0)
		return (LINK);
	else if (are_nums(*line) == 0)
		return (ANT);
	else
		return (WRONG_DATA);
}
