/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <oleksandr32riabyi@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 11:56:48 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:56:49 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				check_data(t_lemin *lemin)
{
	if (lemin->end == NULL)
		return (NO_END_ROOM);
	else if (lemin->start == NULL)
		return (NO_START_ROOM);
	return (OK);
}

void			clear_excess_help(t_lemin *lemin, t_room **head)
{
	t_room		*next;

	if (lemin->end && (*head)->num == lemin->end->num)
		lemin->end = NULL;
	if (lemin->start && (*head)->num == lemin->start->num)
		lemin->start = NULL;
	next = (*head)->next;
	if ((*head)->next)
		(*head)->next->prev = (*head)->prev;
	if ((*head)->prev)
		(*head)->prev->next = (*head)->next;
	free((*head)->name);
	free((*head));
	(*head) = next;
}

void			clear_excess(t_lemin *lemin, t_room *head)
{
	head = lemin->rooms;
	while (head->prev)
		head = head->prev;
	while (head)
	{
		if (head->oppo == NULL)
		{
			clear_excess_help(lemin, &head);
		}
		else
			head = head->next;
	}
	head = lemin->rooms;
	while (head->prev)
		head = head->prev;
	lemin->rooms = head;
}

int				main(int ac, char **av)
{
	char		*line;
	t_lemin		lemin;

	lemin = (t_lemin){0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL};
	get_flags(&lemin.flags, ac, (av + 1));
	approve_flags(lemin.flags);
	line = parse_all(&lemin);
	if (!lemin.end || !lemin.end->oppo
		|| !lemin.start || !lemin.start->oppo)
		check_code(&lemin, WRONG_DATA);
	clear_excess(&lemin, NULL);
	get_ways(&lemin);
	flags_proc(&lemin, line);
	move_ants(&lemin);
	return (0);
}
