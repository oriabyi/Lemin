cmake_minimum_required(VERSION 3.12)
project(Lemin C)

set(CMAKE_C_STANDARD 11)
set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)

include_directories(includes)

add_executable(Lemin
        includes/lem_in.h
        src/ants.c
        src/auxiliary.c
        src/clean.c
        src/clean_rooms.c
        src/error_check.c
        src/flags.c
        src/get_ways.c
        src/get_ways_dop.c
        src/get_ways_dop1.c
        src/main.c
        src/parse_links.c
        src/parse_links_dop.c
        src/parse_rooms.c
        src/parse_rooms_dop.c
        src/parsing.c
        src/print_ways_and_ants.c)

target_link_libraries(Lemin ${LIBFT})