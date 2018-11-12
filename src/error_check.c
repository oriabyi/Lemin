/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:04:42 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:24:43 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		exit_message(t_lemin *lemin, char *message, int code)
{
	ft_putendl_fd(message, 2);
	clean_all(lemin);
	exit(code);
}

void		check_code_contin(t_lemin *lemin, int code)
{
	if (code == FIRST_CHR_ROOM_L)
		exit_message(lemin, "ERROR: *NAME OF ROOM CANT BE \'L\'!", code);
	else if (code == MULTI_MAIN_ROOMS)
		exit_message(lemin, "ERROR: MULTI MAIN ROOMS!", code);
	else if (code == MULTI__ROOMS)
		exit_message(lemin, "ERROR: MULTI ROOMS!", code);
	else if (code == BAD_LINKS)
		exit_message(lemin, "ERROR: WRONG LINK DATA!", code);
	else if (code == WRONG_DATA)
		exit_message(lemin, "WRONG DATA!", WRONG_DATA);
	else
		exit_message(lemin, "ERROR!", ERROR);
}

void		check_code(t_lemin *lemin, int code)
{
	if (code == 0)
		return ;
	if (code == WRONG_PLACE_ANTS)
		exit_message(lemin, "ERROR: WRONG PLACE ANTS!", code);
	else if (code == WRONG_PLACE_ROOMS)
		exit_message(lemin, "ERROR: WRONG PLACE FOR ROOMS!", code);
	else if (code == WRONG_PLACE_LINKS)
		exit_message(lemin, "ERROR: WRONG PLACE OF CONNECTIONS!", code);
	else if (code == WRONG_DATA_ROOMS)
		exit_message(lemin, "ERROR: WRONG ROOM DATA!", code);
	else if (code == NO_ROOM)
		exit_message(lemin, "ERROR: NO ROOM FOUND!", code);
	else if (code == MEMORY_ERROR)
		exit_message(lemin, "ERROR: MEMORY ERROR!", code);
	else if (code == WRONG_QUANTITY_ANTS)
		exit_message(lemin, "ERROR: THE PROBLEM WITH THE NUM OF ANTS!", code);
	else if (code == NO_LINKS)
		exit_message(lemin, "ERROR: THERE ARE NO LINKS!", code);
	else if (code == NO_START_ROOM)
		exit_message(lemin, "ERROR: THERE IS NO START ROOM!", code);
	else if (code == NO_END_ROOM)
		exit_message(lemin, "ERROR: THERE IS NO END ROOM!", code);
	else
		check_code_contin(lemin, code);
}
