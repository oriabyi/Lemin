/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:26:05 by ariabyi           #+#    #+#             */
/*   Updated: 2018/11/01 16:26:06 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
# define LEM_IN_LEM_IN_H

# include <stdio.h>
# include "libft/libft.h"

# define RESET			"\x1b[0m"
# define MAGENTA		"\x1b[35m"
# define CYAN			"\x1b[36m"
# define L_RED			"\x1b[91m"
# define L_BLUE			"\x1b[94m"
# define L_MAGENTA		"\x1b[95m"

# define OK						0
# define ERROR					1

# define NOVISITED				0
# define WAITING				1
# define VISITED				2
# define BLOCKED				3

# define WRONG_PLACE_ROOMS		2
# define WRONG_PLACE_LINKS		3
# define WRONG_PLACE_ANTS		4
# define WRONG_QUANTITY_ANTS	5
# define WRONG_DATA_ROOMS		6
# define WRONG_ARGUMENTS		7
# define FIRST_CHR_ROOM_L		8

# define NO_ROOM				9
# define NO_LINKS				10
# define NO_WAYS				11
# define NO_END_ROOM			12
# define NO_START_ROOM			13
# define MULTI_MAIN_ROOMS		14
# define MULTI__ROOMS			15
# define MEMORY_ERROR			16

typedef struct s_room	t_room;

typedef struct			s_oppo
{
	t_room				*room;
	struct s_oppo		*next;
}						t_oppo;

struct					s_room
{
	char				*name;
	int					x;
	int					y;
	int					num;
	int					stat;
	int					depth;

	struct s_room		*next;
	struct s_room		*prev;
	struct s_oppo		*oppo;
};

typedef struct			s_way
{
	t_room				*rooms;
	struct s_way		*next;
}						t_way;

typedef struct			s_ant
{
	int					num;
	t_way				*way;
	struct s_ant		*next;
}						t_ant;

typedef	struct			s_flags
{
	uint8_t				color_on;
	uint8_t				hide_map;
	uint8_t				approve_flags;
	uint8_t				one_way;
	uint8_t				show_ways;
}						t_flags;

typedef struct			s_ways
{
	t_way				*way;
	int					depth;
	struct s_ways		*next;
}						t_ways;

typedef struct			s_lemin
{
	int					quant_ants;
	int					num_rooms;
	int					number_of_ways;

	t_flags				*flags;
	t_ant				*ant;
	t_room				*start;
	t_room				*end;
	t_room				*rooms;
	t_ways				*ways;
}						t_lemin;

/*
** parse
*/
char					*parse_all(t_lemin *lemin);
int						check_data(t_lemin *lemin);
t_room					*get_room_by_name(t_lemin *lemin, char *name);

/*
** parse links
*/
int						get_links(t_lemin *lemin, char **ret);
int						fill_links(t_lemin *lemin, char *line);

/*
** parse links help
*/
int						add_oppo(t_room *first_main, t_room *second_main);

/*
** parse rooms
*/
int						get_rooms(t_lemin *lemin, char **ret);

/*
** parse rooms help
*/
void					free_char_matrix(char **str);

/*
** parse help
*/
int						check_line(char *line);
void					check_code(t_lemin *lemin, int code);

/*
** flags
*/
void					get_flags(t_flags **flags, int ac, char **av);
void					approve_flags(t_flags *flags);
void					print_map(char *line, uint8_t color_on);
void					flags_proc(t_lemin *lemin, char *line);

/*
** ants
*/
void					move_ants(t_lemin *lemin);

/*
** clean
*/
void					clean_all(t_lemin *lemin);
void					clean_rooms(t_lemin *lemin);
void					clean_ways(t_ways **ways);

/*
** print
*/
void					print_ants(t_lemin *lemin, char *buff);
void					print_ways(t_lemin *lemin);

/*
** get ways
*/
void					get_ways(t_lemin *lemin);
t_ways					*create_way(t_room *tail);
t_way					*create_way_nexus(t_room *room);
void					concat_way_nexus(t_way **phial, t_room *room);
t_room					*get_next_way(t_way **phial);
void					concat_ways(t_lemin *lemin, t_ways *way);

/*
** auxiliary
*/
void					ft_putstr_fd_free(char *s, int fd);
void					exit_message(t_lemin *lemin, char *message, int code);

#endif
