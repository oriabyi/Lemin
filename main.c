/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:33:15 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/01 14:33:16 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				check_data(t_lemin *lemin)
{
	if (lemin->end == NULL)
		return (NO_END_ROOM);
	else if (lemin->start == NULL)
		return (NO_START_ROOM);
	return (OK);
}

int				main(int ac, char **av)
{
	char		*line;
	t_lemin		lemin;

	lemin = (t_lemin){0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL};
	get_flags(&lemin.flags, ac, (av + 1));
	approve_flags(lemin.flags);
	line = parse_all(&lemin);
	get_ways(&lemin);
	flags_proc(&lemin, line);
	move_ants(&lemin);
	return (0);
}
