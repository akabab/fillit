#ifndef FILLIT_H
# define FILLIT_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

# define CHAR_EMPTY				'.'
# define CHAR_BLOCK				'#'

# define TETRIMINO_WIDTH		(4 + 1)
# define TETRIMINO_HEIGHT		4
# define MAX_TETRIMINOS			26
# define MAX_TETRIMINO_SIZE		(TETRIMINO_WIDTH * TETRIMINO_HEIGHT)
# define BUFFER_SIZE			(MAX_TETRIMINOS * (MAX_TETRIMINO_SIZE + 1))

# define TETRI_PATTERNS_COUNT	19

# define FILLIT_DEBUG			1

typedef enum	e_mask
{
	TOP_MASK    = 0xF000, // 1111 0000 0000 0000
	LEFT_MASK   = 0x8888, // 1000 1000 1000 1000
	BOTTOM_MASK = 0x000F, // 0000 0000 0000 1111
	RIGHT_MASK  = 0x1111 
}				t_mask;

typedef enum	e_mask64
{
	TOP_MASK64 = 0xFF00000000000000,
	LEFT_MASK64 = 0x8080808080808080,
	BOTTOM_MASK64 = 0x00000000000FF,
	RIGHT_MASK64 = 0x101010101010101
}				t_mask64;

typedef union	u_bit_form
{
	uint16_t	part[4];
	uint64_t	full;
}				t_bit_form;

typedef struct	s_pattern
{
	char		raw[16];
	uint16_t	value;
	int			gap_x;
}				t_pattern;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_tetrimino
{
	int			pattern_index;
	t_bit_form	bits;
	uint16_t	value;
	uint64_t	new_value;
	int			width;
	int			height;
	t_pos		offset;
	int			new_offset;
	int			max_offset;
	int			limit_line;
}				t_tetrimino;

typedef struct	s_map
{
	t_tetrimino	t[MAX_TETRIMINOS];
	int			t_count;
	int			size;
	uint64_t	map1;
	uint64_t	map2;
	uint64_t	map3;
	uint16_t	m[16];
	uint16_t	mdz[16];
	int			space;
	int			total_space;
	int			space_required;
	t_pos		dyn_pos[19];
	int			new_dynpos[19];
}				t_map;

/*
 **				parse.c
 */
void			parse(int fd, t_map *map);
void			parse_entry(char *entry, t_map *map);

/*
 **				pattern.c
 */
int				get_matched_pattern_index(uint16_t value);

/*
 **				binary.c
 */
uint16_t		raw_to_binary_represention(char *raw);

/*
 **				solve.c
 */
void			solve(t_map *map);

/*
 **				dz.c
 */
t_bool			is_enough_space(t_map *map);

/*
 **				print.c
 */
void			print_value_bits(uint16_t value, int sep, int n);
void			print_map(uint16_t map[], int map_size);
void			print_result_map(t_map *map);
void print_tetriminos(int toto);
void			print_tetriminos_long(unsigned long toto);
void			print_dyn_map(t_map *map, unsigned int line_size);
void			print_dyn_piece(uint64_t value, unsigned int line_size);

/*
 **				utils.c
 */
int				ft_ceil_sqrt(int n);

/*
 **				error.c
 */
void			fillit_error_msg_exit(char *message);

uint64_t		new_form(uint64_t tetriminos, int newline_size);
int64_t     move_to_most_top_left64_position(uint64_t value);

#endif
