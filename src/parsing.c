/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:03:48 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:26:03 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				check_line_ants(char *line)
{
	int			i;

	i = 0;
	if (line == NULL)
		return (1);
	while (*line)
	{
		if (*line == '-' || (*line >= '0' && *line <= '9'))
			break ;
		line++;
	}
	if (*line == '-')
		i++;
	while (*line && (*line >= '0' && *line <= '9'))
	{
		line++;
		i++;
	}
	return (i);
}

int				ant_code(int *quant_ants, char **ret, int *code, char *line)
{
	*quant_ants = ft_atoi(line);
	if (*quant_ants > 0 && check_line_ants(line) == ft_pwrbase(*quant_ants, 10))
		*code = OK;
	else
		*code = WRONG_QUANTITY_ANTS;
	if (*code == OK)
		*ret = ft_multjoinfr(4, NULL, *ret, line, "\n");
	else
		*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
	return (1);
}

int				get_quant_ants(int *quant_ants, char **ret, char *line)
{
	int			code;

	while ((code = gnl(0, &line)) && !(*quant_ants))
	{
		code = what_the_line_is(&line);
		if (code == COMMENT || code == COMMAND)
		{
			*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
			continue ;
		}
		if (code == BAD_LINE)
			break ;
		else if (code == ANT && ant_code(quant_ants, ret, &code, line))
			break ;
		else if (code == LINK)
			return (free_str_return_int(&line, WRONG_PLACE_LINKS));
		else if (code == ROOM || code == MAIN_ROOM)
			return (free_str_return_int(&line, WRONG_PLACE_ROOMS));
		else if (code == WRONG_DATA)
			return (free_str_return_int(&line, WRONG_QUANTITY_ANTS));
		*ret = ft_multjoinfr(5, NULL, *ret, NULL, line, "\n");
	}
	(code == 0 && line) ? free(line) : 0;
	return (*quant_ants ? code : WRONG_QUANTITY_ANTS);
}

void			copy_oppos_start_end(t_lemin *lemin)
{
	char		*tofree;

	tofree = lemin->start->name;
	free(lemin->start);
	lemin->start = get_room_by_name(lemin, lemin->start->name);
	free(tofree);
	free(lemin->end);
	tofree = lemin->end->name;
	lemin->end = get_room_by_name(lemin, lemin->end->name);
	free(tofree);
}

char			*parse_all(t_lemin *lemin)
{
	char		*ret;
	int			code;

	ret = NULL;
	code = get_quant_ants(&(lemin->quant_ants), &ret, NULL);
	if (code == OK)
		code = get_rooms(lemin, &ret);
	if (code == OK)
		code = get_links(lemin, &ret);
	check_code(lemin, code);
	check_code(lemin, check_data(lemin));
	copy_oppos_start_end(lemin);
	return (ret);
}
