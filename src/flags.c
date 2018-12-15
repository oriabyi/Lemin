/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabyi <oleksandr32riabyi@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:38:40 by oriabyi           #+#    #+#             */
/*   Updated: 2018/11/02 11:24:50 by oriabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				get_flags_help(t_flags *flags, char *av)
{
	if (!av || !*av)
		return (1);
	while (*av)
	{
		if (*av == 'c')
			flags->color_on = 1;
		else if (*av == 'h')
			flags->hide_map = 1;
		else if (*av == 'a')
			flags->approve_flags = 1;
		else if (*av == 'o')
			flags->one_way = 1;
		else if (*av == 's')
			flags->show_ways = 1;
		else
			return (1);
		av++;
	}
	return (0);
}

void			get_flags(t_flags **flags, int ac, char **av)
{
	if (ac == 1 || !av)
		return ;
	if (!(*flags = (t_flags *)malloc(sizeof(t_flags))))
		exit(MEMORY_ERROR);
	while (*av)
	{
		if (ft_strcmp(*av, "-c") == 0)
			(*flags)->color_on = 1;
		else if (ft_strcmp(*av, "-h") == 0)
			(*flags)->hide_map = 1;
		else if (ft_strcmp(*av, "-a") == 0)
			(*flags)->approve_flags = 1;
		else if (ft_strcmp(*av, "-o") == 0)
			(*flags)->one_way = 1;
		else if (ft_strcmp(*av, "-s") == 0)
			(*flags)->show_ways = 1;
		else if (**av == '-')
			if (get_flags_help((*flags), (*av + 1)) == 1)
			{
				free((*flags));
				ft_putstr_fd("Usage: ./lem-in [-chaos] < map\n", 2);
				exit(WRONG_ARGUMENTS);
			}
		av++;
	}
}

void			ft_putstr_fd_free(char *s, int fd)
{
	if (!s || !*s || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
	ft_strdel(&s);
}

void			approve_flags(t_flags *flags)
{
	char		*buf;
	char		*color;

	if (!flags || !flags->approve_flags)
		return ;
	if (flags->color_on)
		color = ft_strdup(L_RED);
	else
		color = ft_strdup(RESET);
	buf = ft_strdup("@");
	buf = ft_multjoinfr(5, color, NULL, buf,
			"color_on\t\t= ", flags->color_on ? "true\n" : "false\n");
	buf = ft_multjoinfr(5, color, NULL, buf,
			"@hide_map\t\t= ", flags->hide_map ? "true\n" : "false\n");
	buf = ft_multjoinfr(5, color, NULL, buf,
			"@approve_flags\t\t= ",
			flags->approve_flags ? "true\n" : "false\n");
	buf = ft_multjoinfr(5, color, NULL, buf,
			"@one_way\t\t= ", flags->one_way ? "true\n" : "false\n");
	buf = ft_multjoinfr(5, color, NULL, buf,
			"@show_ways\t\t= ", flags->show_ways ? "true\n" : "false\n");
	buf = ft_multjoinfr(4, NULL, buf, RESET, "\n");
	buf ? ft_putstr_fd_free(buf, 2) : ft_strdel(&buf);
	free(color);
}

void			flags_proc(t_lemin *lemin, char *line)
{
	if (lemin->ways == NULL)
	{
		free(line);
		exit_message(lemin, "ERROR: NO WAYS!", NO_WAYS);
	}
	if (lemin->flags && lemin->flags->one_way)
		clean_ways(&lemin->ways->next);
	if (lemin->flags && lemin->flags->show_ways)
		print_ways(lemin);
	if (!lemin->flags)
		print_map(line, 0);
	if (lemin->flags && lemin->flags->hide_map == 0)
		print_map(line, lemin->flags->color_on);
}
