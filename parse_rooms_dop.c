/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms_dop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:52:56 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/01 15:52:57 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_char_matrix(char **str)
{
	int		counter;

	counter = 0;
	while (str[counter])
		free(str[counter++]);
	free(str);
}
