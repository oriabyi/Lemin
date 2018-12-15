/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabyi <oleksandr32riabyi@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:05:59 by oriabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:25:25 by oriabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

void			fill_links_get_names(t_lemin *lemin, char **first,
					char **second, char *line)
{
	size_t		i;
	size_t		temp;
	char		*temp_str;
	int			room_num;
	t_room		*temp_room;

	i = 1;
	temp = ft_strlen(line);
	while (i <= temp)
	{
		room_num = lemin->num_rooms;
		temp_str = ft_strsub(line, 0, i);
		while (room_num-- && !*first)
		{
			if ((temp_room = get_room_by_name(lemin, temp_str)))
			{
				*first = ft_strdup(temp_room->name);
				*second = ft_strdup(line + ft_strlen(*first) + 1);
			}
		}
		ft_strdel(&temp_str);
		if (*first)
			break ;
		i++;
	}
}

int				fill_links(t_lemin *lemin, char *line)
{
	int			code;
	char		*first;
	char		*second;

	first = NULL;
	second = NULL;
	if (count_chars(line, '-') > 1)
		fill_links_get_names(lemin, &first, &second, line);
	else
	{
		if ((first = get_name_link(line)) && *first != '\0')
			second = get_name_link(line + ft_strlen(first) + 1);
		else
			second = NULL;
	}
	if (first && second && *first != '\0' && *second != '\0')
		code = add_oppos(lemin, first, second);
	else
		code = BAD_LINKS;
	free(first);
	free(second);
	return (code);
}

int				get_links_help(t_lemin *lemin, int *code, char *line)
{
	if (*code == ANT)
		return (free_str_return_int(&line, WRONG_PLACE_ANTS));
	else if (*code == LINK)
	{
		if ((*code = fill_links(lemin, line)))
			return (free_str_return_int(&line, *code));
	}
	else if (*code == ROOM || *code == MAIN_ROOM)
		return (free_str_return_int(&line, WRONG_PLACE_ROOMS));
	else if (*code == WRONG_DATA)
		return (free_str_return_int(&line, WRONG_DATA));
	return (*code);
}

int				get_links(t_lemin *lemin, char **ret)
{
	char		*line;
	int			code;

	while ((code = gnl(0, &line)))
	{
		code = what_the_line_is(&line);
		if (code == BAD_LINE)
			break ;
		else if (code == COMMENT || code == COMMAND)
		{
			*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
			continue ;
		}
		else if ((code = get_links_help(lemin, &code, line)))
			return (code);
		*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
	}
	if (code == 0)
		free(line);
	return (OK);
}
