/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ways_and_ants.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:01:14 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:26:16 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			print_ways_help(char **buff, t_ways *ways)
{
	while (ways->way)
	{
		*buff = ft_multjoinfr(3, NULL, *buff, ways->way->rooms->name);
		ways->way = ways->way->next;
		if (ways->way)
			*buff = ft_multjoinfr(3, NULL, *buff, " -> ");
		else if (!ways->way)
			*buff = ft_multjoinfr(6, NULL, *buff, " | ", NULL,
					ft_itoa(ways->depth), "\n");
	}
}

void			print_ways(t_lemin *lemin)
{
	t_ways		*temp_ways;
	t_way		*temp_way;
	char		*buff;

	if (lemin->flags && lemin->flags->color_on)
		buff = ft_strdup(L_BLUE);
	else
		buff = NULL;
	temp_ways = lemin->ways;
	while (lemin->ways)
	{
		temp_way = lemin->ways->way;
		print_ways_help(&buff, lemin->ways);
		lemin->ways->way = temp_way;
		lemin->ways = lemin->ways->next;
	}
	buff = ft_multjoinfr(4, NULL, buff, "\n", RESET);
	write(1, buff, ft_strlen(buff));
	free(buff);
	lemin->ways = temp_ways;
}

void			antzero(t_lemin *lemin)
{
	t_ant		*head;
	t_room		*temp;

	if (!lemin)
		return ;
	temp = NULL;
	head = lemin->ant;
	while (head)
	{
		if (head->way)
			temp = head->way->rooms;
		while (head->way && temp)
		{
			temp->stat = 0;
			temp = temp->next;
		}
		head = head->next;
	}
}

void			print_ants_help(t_lemin *lemin, t_ant **head, char **buff)
{
	if ((*head)->way)
	{
		if ((*head)->way->rooms->num == lemin->end->num)
			lemin->quant_ants--;
		if (((*head)->way->rooms->stat == 1 && (*head)->way->rooms->depth ==
			(*head)->num) || (*head)->way->rooms->num == lemin->start->num)
			(*head)->way = (*head)->way->next;
	}
	(*head) = (*head)->next;
	if (!(*head))
	{
		(*head) = lemin->ant;
		antzero(lemin);
		lemin->number_of_ways = 0;
		if (*buff)
			*buff = ft_multjoinfr(3, NULL, *buff, "\n");
	}
}

void			print_ants(t_lemin *lemin, char *buff)
{
	t_ant		*head;
	char		*temp;
	char		*cl[2];

	head = lemin->ant;
	cl[0] = (lemin->flags && lemin->flags->color_on) ? L_MAGENTA : RESET;
	cl[1] = (lemin->flags && lemin->flags->color_on) ? MAGENTA : RESET;
	while (lemin->quant_ants > 0)
	{
		if (head->way && (!head->way->rooms->stat || head->way->rooms->num ==
			lemin->end->num) && head->way->rooms->num != lemin->start->num)
		{
			if (buff && lemin->number_of_ways == 1)
				buff = ft_multjoinfr(3, NULL, buff, " ");
			temp = ft_multjoinfr(8, cl[0], "L", NULL, ft_itoa(head->num), cl[1],
					"-", cl[0], head->way->rooms->name);
			buff = ft_multjoinfr(4, NULL, buff, NULL, temp);
			head->way->rooms->stat = 1;
			head->way->rooms->depth = head->num;
			lemin->number_of_ways = 1;
		}
		print_ants_help(lemin, &head, &buff);
	}
	ft_putstr_fd_free((buff = ft_multjoinfr(4, NULL, buff, RESET, "\n")), 1);
}
