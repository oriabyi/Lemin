/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links_dop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:40:54 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/01 15:40:55 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			concat_oppo(t_room *room, t_oppo *neigh)
{
	t_oppo		*temp;

	if (!room->oppo)
		room->oppo = neigh;
	else
	{
		temp = room->oppo;
		while (temp->next)
			temp = temp->next;
		temp->next = neigh;
	}
}

t_oppo			*create_oppo(void)
{
	t_oppo		*ret;

	if (!(ret = (t_oppo *)malloc(sizeof(t_oppo))))
		return (NULL);
	*ret = (t_oppo){NULL, NULL};
	return (ret);
}

int				add_oppo(t_room *first_main, t_room *second_main)
{
	int			code;
	t_oppo		*first;
	t_oppo		*second;

	code = OK;
	if (!(first = create_oppo()))
		return (MEMORY_ERROR);
	if (!(second = create_oppo()))
		return (MEMORY_ERROR);
	first->room = first_main;
	first->next = NULL;
	concat_oppo(second_main, first);
	second->room = second_main;
	second->next = NULL;
	concat_oppo(first_main, second);
	return (code);
}
