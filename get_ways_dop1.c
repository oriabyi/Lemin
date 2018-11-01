/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ways_dop1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:47:12 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/01 14:51:10 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_way			*create_way_nexus(t_room *room)
{
	t_way		*res;

	if (!(res = (t_way *)malloc(sizeof(t_way))))
		return (NULL);
	res->next = NULL;
	res->rooms = room;
	return (res);
}

t_ways			*create_way(t_room *back)
{
	t_ways	*ret;
	t_way	*head;

	if (!(ret = (t_ways *)malloc(sizeof(t_ways))))
		return (NULL);
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
