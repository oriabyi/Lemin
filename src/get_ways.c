/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ways.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:43:46 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:24:59 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			find_oppos(t_way **phial, t_room *cur)
{
	t_oppo		*oppo;

	oppo = cur->oppo;
	while (oppo)
	{
		if (oppo->room->stat == NOVISITED)
		{
			oppo->room->stat = WAITING;
			oppo->room->depth = cur->depth + 1;
			if (cur->prev && cur->prev->num == oppo->room->num)
				oppo->room->prev = cp_room(cur);
			else
				oppo->room->prev = cur;
			concat_way_nexus(phial, oppo->room);
		}
		oppo = oppo->next;
	}
}

t_ways			*get_all_ways(t_lemin *lemin, t_room *cur,
		t_room *end, t_way **phial)
{
	t_ways		*ret;

	ret = NULL;
	if (!cur)
		return (NULL);
	cur->stat = VISITED;
	if (cur->num == end->num)
		return (create_way(lemin, cur));
	find_oppos(phial, cur);
	if (*phial)
		ret = get_all_ways(lemin, get_next_way(phial), end, phial);
	return (ret);
}

void			set_default(t_lemin *lemin)
{
	t_room		*temp;

	lemin->end->prev = NULL;
	lemin->end->stat = NOVISITED;
	temp = lemin->rooms;
	while (temp)
	{
		if (temp->stat != BLOCKED)
		{
			temp->stat = NOVISITED;
			temp->depth = 0;
			temp->prev = NULL;
		}
		temp = temp->next;
	}
}

void			free_phial(t_way *phial)
{
	t_way		*tofree;

	tofree = phial;
	while (tofree)
	{
		tofree = phial->next;
		free(phial);
		phial = tofree;
	}
}

void			get_ways(t_lemin *lemin)
{
	t_way	*phial;
	t_ways	*res;

	phial = NULL;
	while (1)
	{
		res = get_all_ways(lemin, lemin->start, lemin->end, &phial);
		free_phial(phial);
		phial = NULL;
		set_default(lemin);
		if (!res)
			break ;
		concat_ways(lemin, res);
		if (res->depth < 2)
			break ;
	}
	res = lemin->ways;
	while (res)
	{
		res->depth--;
		res = res->next;
	}
}
