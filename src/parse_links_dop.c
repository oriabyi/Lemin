/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links_dop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabyi <oleksandr32riabyi@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:40:54 by oriabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:25:35 by oriabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				is_oppo(t_room *room, int num)
{
	t_oppo		*head;

	head = room->oppo;
	while (head)
	{
		if (head->room && head->room->num == num)
			return (1);
		head = head->next;
	}
	return (0);
}

int				add_oppos(t_lemin *lemin, char *first, char *second)
{
	t_room		*temp_first;
	t_room		*temp_second;

	if (!(temp_first = get_room_by_name(lemin, first)))
		return (BAD_LINKS);
	if (!(temp_second = get_room_by_name(lemin, second)))
		return (BAD_LINKS);
	if (is_oppo(temp_first, temp_second->num) == 0)
		return (add_oppo(temp_first, temp_second));
	return (OK);
}

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
