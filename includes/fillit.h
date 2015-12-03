#ifndef __FILLIT_H__
# define __FILLIT_H__

# include "stdint.h"

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

typedef struct	s_tetrimino
{
	int			index;
	char		*raw;
	uint16_t	value;
	uint16_t	v[4];
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

/*
**		parse.c
*/
int			parse(int fd, t_tetrimino tetriminos[]);

/*
**		move.c
*/
int			move(int value, t_direction direction);

// DEBUG
void	print_16bit_representation_of_int(uint16_t value);

#endif