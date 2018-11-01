/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:02:53 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/01 16:02:54 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				check_line(char *line)
{
	if (!line || *line == '\0' || *line == '\n')
	{
		if (line && (*line == '\0' || *line == '\n'))
			free(line);
		return (1);
	}
	return (0);
}
