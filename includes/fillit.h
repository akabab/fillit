#ifndef FILLIT_H
# define FILLIT_H

# include <stdint.h>
# include "libft.h"

# define CHAR_EMPTY				'.'
# define CHAR_BLOCK				'#'

# define TETRIMINO_WIDTH		(4 + 1)
# define TETRIMINO_HEIGHT		4
# define MAX_TETRIMINOS			26
# define MAX_TETRIMINO_SIZE		(TETRIMINO_WIDTH * TETRIMINO_HEIGHT)
# define BUFFER_SIZE			(MAX_TETRIMINOS * (MAX_TETRIMINO_SIZE + 1))

# define TETRI_PATTERNS_COUNT	19

# define FILLIT_DEBUG			0

typedef enum	e_mask
{
	TOP_MASK = 0xF000,
	LEFT_MASK = 0x8888,
	BOTTOM_MASK = 0x000F,
	RIGHT_MASK = 0x1111
}				t_mask;

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
	int			width;
	int			height;
	t_pos		offset;
}				t_tetrimino;

typedef struct	s_map
{
	t_tetrimino	t[MAX_TETRIMINOS];
	int			t_count;
	int			size;
	uint16_t	m[16];
	uint16_t	mdz[16];
	int			total_space;
	int			space_required;
	t_pos		dyn_pos[19];
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

/*
**				utils.c
*/
int				ft_ceil_sqrt(int n);

/*
**				error.c
*/
void			fillit_error_msg_exit(char *message);

#endif
