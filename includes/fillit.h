#ifndef __FILLIT_H__
# define __FILLIT_H__

# define CHAR_EMPTY		'.'
# define CHAR_BLOCK		'#'

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
	int			value; // top-left binary value	
}				t_tetrimino;

#endif