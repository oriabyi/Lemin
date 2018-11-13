/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <oleksandr32riabyi@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:04:14 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:24:04 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_ant			*get_ant(int *num_of_ant)
{
	t_ant		*ret;

	if (!(ret = (t_ant *)malloc(sizeof(t_ant))))
		return (NULL);
	*ret = (t_ant){0, NULL, NULL};
	ret->num = (*num_of_ant)++;
	return (ret);
}

void			initialize_ants(t_lemin *lemin)
{
	short		quan_ants;
	t_ant		*temp_ant;
	int			num_of_ant;

	num_of_ant = 1;
	quan_ants = (short)lemin->quant_ants;
	lemin->ant = get_ant(&num_of_ant);
	temp_ant = lemin->ant;
	while (--quan_ants)
	{
		temp_ant->next = get_ant(&num_of_ant);
		temp_ant = temp_ant->next;
	}
}

void			check_alg(t_lemin *lemin, int temp_ants)
{
	int			depth_ways;
	t_ways		*temp_ways;

	depth_ways = 0;
	temp_ways = lemin->ways;
	while (temp_ways)
	{
		if (temp_ways->depth > temp_ants)
			depth_ways++;
		temp_ways = temp_ways->next;
	}
	if (depth_ways == lemin->number_of_ways)
	{
		temp_ways = lemin->ways;
		while (temp_ways)
		{
			temp_ways->depth--;
			temp_ways = temp_ways->next;
		}
	}
}

void			fill_ants(t_lemin *lemin)
{
	t_ways		*head;
	t_ant		*ant_head;
	int			temp_ants;

	temp_ants = lemin->quant_ants;
	head = lemin->ways;
	ant_head = lemin->ant;
	while (ant_head && temp_ants)
	{
		if (head)
		{
			check_alg(lemin, temp_ants);
			if (head->depth <= temp_ants || lemin->number_of_ways == 1)
			{
				ant_head->way = head->way;
				ant_head = ant_head->next;
				temp_ants--;
			}
			head = head->next;
		}
		else
			head = lemin->ways;
	}
}

void			move_ants(t_lemin *lemin)
{
	initialize_ants(lemin);
	fill_ants(lemin);
	print_ants(lemin, NULL);
	clean_all(lemin);
}
