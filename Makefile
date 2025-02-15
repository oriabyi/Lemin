# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#   By: oriabyi <oleksandr32riabyi@gmail.com>      +#+  +:+       +#+          #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/21 15:21:59 by oriabyi           #+#    #+#              #
#    Updated: 2018/11/02 11:59:35 by oriabyi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:         all clean fclean re

CC = gcc
NAME = lem-in
SRCDIR = src/
SRC =	$(SRCDIR)ants.c					\
		$(SRCDIR)clean.c				\
		$(SRCDIR)clean_rooms.c 			\
		$(SRCDIR)flags.c				\
		$(SRCDIR)get_ways.c				\
		$(SRCDIR)get_ways_dop.c			\
		$(SRCDIR)get_ways_dop1.c		\
		$(SRCDIR)main.c					\
		$(SRCDIR)error_check.c			\
		$(SRCDIR)parse_links.c			\
		$(SRCDIR)parse_links_dop.c		\
		$(SRCDIR)parse_rooms.c			\
		$(SRCDIR)parse_rooms_dop.c		\
		$(SRCDIR)parsing.c				\
		$(SRCDIR)print_ways_and_ants.c	\
		$(SRCDIR)auxiliary.c				

CFLAGS = -Wall -Wextra -Werror
LIBDIR = ./libft/
HEADER = -I ./includes -I $(LIBDIR)/libft.h
LIBINCL = -L. $(LIBDIR)/libft.a
OBJFOLD = ./.obj/
OBJ = $(addprefix $(OBJFOLD), $(SRC:.c=.o))

all:            $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBDIR) -f Makefile
	$(CC) $(CFLAGS) $(LIBINCL) $(HEADER) -o $(NAME) $(OBJ) 
	@echo "lem_in: done"

$(OBJFOLD)%.o: %.c
	@mkdir -p $(OBJFOLD)$(SRCDIR)
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $<

clean:
	@rm -rf $(OBJFOLD)
	@make -C $(LIBDIR) -f Makefile clean
	@echo "objects removed"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBDIR) -f Makefile fclean
	@echo "binary removed"

re:             fclean all

