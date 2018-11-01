/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:03:48 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/01 15:03:50 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				get_quant_ants(int *quant_ants, char **ret)
{
	char		*line;

	while (gnl(0, &line) && !(*quant_ants))
	{
		if (check_line(line) == 1)
			break ;
		else if (!(*quant_ants))
		{
			*quant_ants = ft_atoi(line);
			if (!are_nums(line) || quant_ants <= 0)
				return (free_str_return_int(&line, WRONG_QUANTITY_ANTS));
			*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
			return (OK);
		}
		else if (!ft_strcmp((line), "##start") || !ft_strcmp((line), "##end"))
			return (free_str_return_int(&line, WRONG_PLACE_ROOMS));
		else if (ft_strchr(line, '-'))
			return (free_str_return_int(&line, WRONG_PLACE_LINKS));
		else if (*line != '#')
			return (free_str_return_int(&line, WRONG_PLACE_ROOMS));
		*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
	}
	return (*quant_ants ? WRONG_QUANTITY_ANTS : OK);
}

void			copy_oppos_start_end(t_lemin *lemin)
{
	char		*tofree;

	tofree = lemin->start->name;
	free(lemin->start);
	lemin->start = get_room_by_name(lemin, lemin->start->name);
	free(tofree);
	free(lemin->end);
	tofree = lemin->end->name;
	lemin->end = get_room_by_name(lemin, lemin->end->name);
	free(tofree);
}

char			*parse_all(t_lemin *lemin)
{
	char		*ret;
	int			code;

	ret = NULL;
	code = get_quant_ants(&(lemin->quant_ants), &ret);
	if (code == OK)
		code = get_rooms(lemin, &ret);
	if (code == OK)
		code = get_links(lemin, &ret);
	check_code(lemin, code);
	check_code(lemin, check_data(lemin));
	copy_oppos_start_end(lemin);
	return (ret);
}
