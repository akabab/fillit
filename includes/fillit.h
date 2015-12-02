#ifndef __FILLIT_H__
# define __FILLIT_H__

# define CHAR_EMPTY				'.'
# define CHAR_BLOCK				'#'

# define TETRIMINO_WIDTH		(4 + 1)
# define TETRIMINO_HEIGHT		4
# define MAX_TETRIMINOS			26
# define MAX_TETRIMINO_SIZE		(TETRIMINO_WIDTH * TETRIMINO_HEIGHT)
# define BUFFER_SIZE			(MAX_TETRIMINOS * (MAX_TETRIMINO_SIZE + 1))

typedef enum	e_mask
{
	TOP_MASK    = 0xF000, // 1111 0000 0000 0000
	LEFT_MASK   = 0xAAAA, // 1000 1000 1000 1000
	BOTTOM_MASK = 0x000F, // 0000 0000 0000 1111
	RIGHT_MASK  = 0x1111  // 0001 0001 0001 0001
}				t_mask;

typedef struct	s_tetrimino
{
	char		index; // [A-Z] index
	char		*raw;
	int			value; // top-left binary value
	int			bi_value;
}				t_tetrimino;

#endif
