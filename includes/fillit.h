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

typedef union	u_t_value
{
	uint16_t	v[4];
	uint64_t	value;
}				t_t_value;

typedef struct	s_tetrimino
{
	int			index;
	char		*raw;
	uint16_t	value;
	uint16_t	v[4];
	int			width;
	int			height;
	int			offset_x;
	int			offset_y;
}				t_tetrimino;

typedef enum	e_direction
{
	TOP    = -4,
	LEFT   = -1,
	BOTTOM = +4,
	RIGHT  = +1
}				t_direction;

typedef struct	s_map
{
	t_tetrimino	t[MAX_TETRIMINOS];
	int			t_count;
	uint16_t	m[16];
	int			size;
}				t_map;

/*
**		parse.c
*/
int			parse(int fd, t_tetrimino tetriminos[]);

/*
**		move.c
*/
int			move(int value, t_direction direction);

/*
**		solve.c
*/
t_bool		solve(t_map *map, int tetri_index);

/*
**		print.c
*/
void		print_16bit_representation_of_int(uint16_t value, int sep);
void		print_map(t_map *map);

#endif