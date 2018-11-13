/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ways_dop1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <oleksandr32riabyi@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:47:12 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:25:12 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_way			*create_way_nexus(t_room *room)
{
	t_way		*res;

	if (!(res = (t_way *)malloc(sizeof(t_way))))
		return (NULL);
	res->next = NULL;
	res->rooms = room;
	return (res);
}

t_ways			*create_way(t_lemin *lemin, t_room *back)
{
	t_ways	*ret;
	t_way	*head;

	if (!(ret = (t_ways *)malloc(sizeof(t_ways))))
		return (NULL);
	(void)lemin;
	ret->depth = back->depth;
	ret->next = NULL;
	ret->way = NULL;
	while (back)
	{
		back->stat = BLOCKED;
		head = create_way_nexus(back);
		head->next = ret->way;
		ret->way = head;
		back = back->prev;
	}
	return (ret);
}
