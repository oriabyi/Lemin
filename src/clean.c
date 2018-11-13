/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <oleksandr32riabyi@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:34:48 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:24:25 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			clean_ants(t_lemin *lemin)
{
	t_ant		*head;
	t_ant		*temp;

	head = lemin->ant;
	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}

void			clean_way(t_way *way)
{
	t_way		*head;
	t_way		*next;

	head = way;
	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

void			clean_ways(t_ways **ways)
{
	t_ways		*head;
	t_ways		*temp;

	head = *ways;
	while (head)
	{
		temp = head->next;
		clean_way(head->way);
		free(head);
		head = temp;
	}
	(*ways) = NULL;
}

void			clean_all(t_lemin *lemin)
{
	clean_rooms(lemin);
	clean_ants(lemin);
	clean_ways(&lemin->ways);
	if (lemin->flags)
		free(lemin->flags);
}
