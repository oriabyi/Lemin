/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabyi <oleksandr32riabyi@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:35:16 by oriabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:24:35 by oriabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			clean_oppo(t_oppo *oppo)
{
	t_oppo		*head;
	t_oppo		*next;

	head = oppo;
	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

void			clean_rooms(t_lemin *lemin)
{
	t_room		*head;
	t_room		*next;

	head = lemin->rooms;
	while (head && head->prev)
		head = head->prev;
	while (head)
	{
		next = head->next;
		free(head->name);
		clean_oppo(head->oppo);
		free(head);
		head = next;
	}
}
