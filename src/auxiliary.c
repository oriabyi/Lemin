/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabyi <oleksandr32riabyi@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:02:53 by oriabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:24:17 by oriabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			print_map(char *line, uint8_t color_on)
{
	if (color_on)
		line = ft_multjoinfr(5, CYAN, NULL, line, RESET, "\n");
	else
		line = ft_multjoinfr(3, NULL, line, "\n");
	write(1, line, ft_strlen(line));
	free(line);
}

int				check_line(char **line)
{
	char		*temp;

	if (line == NULL || *line == NULL)
		return (1);
	if (**line == '\0' || **line == '\n')
	{
		ft_strdel(line);
		return (1);
	}
	temp = *line;
	while (*temp)
	{
		if (ft_isascii(*temp) == 0)
		{
			ft_strdel(line);
			return (1);
		}
		temp++;
	}
	return (0);
}

t_room			*cp_room(t_room *room)
{
	t_room		*ret;

	ret = (t_room *)malloc(sizeof(t_room));
	ret->name = ft_strdup(room->name);
	ret->num = room->num;
	ret->stat = room->stat;
	ret->depth = room->depth;
	ret->prev = NULL;
	return (ret);
}

int				count_chars(char *s, char c)
{
	int			i;

	if (!s)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}
