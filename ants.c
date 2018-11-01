/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:04:14 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/01 16:04:15 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void			print_map(char *line, uint8_t color_on)
{
	if (color_on)
		line = ft_multjoinfr(5, CYAN, NULL, line, RESET, "\n");
	else
		line = ft_multjoinfr(3, NULL, line, "\n");
	write(1, line, ft_strlen(line));
	free(line);
}

void			move_ants(t_lemin *lemin)
{
	initialize_ants(lemin);
	fill_ants(lemin);
	print_ants(lemin, NULL);
	clean_all(lemin);
}
