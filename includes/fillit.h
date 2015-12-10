#ifndef __FILLIT_H__
# define __FILLIT_H__

# include <stdint.h>
# include "libft.h"

# include <stdio.h> //

# define CHAR_EMPTY				'.'
# define CHAR_BLOCK				'#'

# define TETRIMINO_WIDTH		(4 + 1)
# define TETRIMINO_HEIGHT		4
# define MAX_TETRIMINOS			26
# define MAX_TETRIMINO_SIZE		(TETRIMINO_WIDTH * TETRIMINO_HEIGHT)
# define BUFFER_SIZE			(MAX_TETRIMINOS * (MAX_TETRIMINO_SIZE + 1))

# define TETRI_PATTERNS_COUNT	19

typedef enum	e_mask
{
	TOP_MASK    = 0xF000, // 1111 0000 0000 0000
	LEFT_MASK   = 0x8888, // 1000 1000 1000 1000
	BOTTOM_MASK = 0x000F, // 0000 0000 0000 1111
	RIGHT_MASK  = 0x1111  // 0001 0001 0001 0001
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
	int			safe_offset_x;
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
**			parse.c
*/
void		parse(int fd, t_map *map);

/*
**			solve.c
*/
void		solve(t_map *map);

/*
**			dz.c
*/
t_bool		is_enough_space(t_map *map);

/*
**			print.c
*/
void		print_16bit_representation_of_int(uint16_t value, int sep, int limit);
void		print_map(uint16_t map[], int size);
void		print_result_map(t_map *map);

/*
**			utils.c
*/
int			ft_ceil_sqrt(int n);

#endif
