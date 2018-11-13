/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ways_dop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <oleksandr32riabyi@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:44:15 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:25:06 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_room			*get_room_by_name(t_lemin *lemin, char *name)
{
	t_room		*temp;

	if (!lemin || !name || !lemin->rooms)
		return (NULL);
	temp = lemin->rooms;
	while (temp->prev)
		temp = temp->prev;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void			concat_ways(t_lemin *lemin, t_ways *way)
{
	t_ways		*ways;

	ways = lemin->ways;
	if (!ways)
		lemin->ways = way;
	else
	{
		while (ways->next)
			ways = ways->next;
		ways->next = way;
	}
	lemin->number_of_ways++;
}

t_room			*get_next_way(t_way **phial)
{
	t_way		*elem;
	t_room		*res;

	elem = *phial;
	*phial = (*phial)->next;
	elem->next = NULL;
	res = elem->rooms;
	free(elem);
	return (res);
}

void			concat_way_nexus(t_way **phial, t_room *room)
{
	t_way		*head;

	if (*phial && room)
	{
		head = *phial;
		while (head->next)
			head = head->next;
		head->next = create_way_nexus(room);
	}
	else if (room)
		*phial = create_way_nexus(room);
}
