#ifndef FILLIT_H
# define FILLIT_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
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


typedef struct	s_map	t_map;

typedef enum			e_mask
{
	TOP_MASK    = 0xF000, // 1111 0000 0000 0000
	LEFT_MASK   = 0x8888, // 1000 1000 1000 1000
	BOTTOM_MASK = 0x000F, // 0000 0000 0000 1111
	RIGHT_MASK  = 0x1111 
}						t_mask;

typedef struct			s_pattern
{
	uint16_t			value;
	short				gap_x;
	short				width;
//	char				raw[16];
	short				height;
}						t_pattern;

typedef struct			s_pos
{
	int					x;
	int					y;
}						t_pos;

typedef struct			s_tetrimino
{
	short				pattern_index;
	short				new_offset;
	short				max_offset;
	short				limit_line;
	short				max_grid;
	short				width;
	short				height;
	short				gap_x;
	uint16_t			value;
	unsigned __int128	new_value;
	t_pos				offset;
}						t_tetrimino;

struct					s_map
{
	t_tetrimino			t[MAX_TETRIMINOS];
	int 				size;
	int					t_count;
	unsigned __int128	grid;
	unsigned __int128	grid_plus;
	int					total_space;
	int					space_required;
	t_pos				dyn_pos[19];
	t_bool				(*resolve)(t_map *, int, int const);
};

/*
 **				parse.c
 */
void					parse(int fd, t_map *map);
void					parse_entry(char *entry, t_map *map);

/*
 **				pattern.c
 */
int						get_matched_pattern_index(t_tetrimino *t);

/*
 **				binary.c
 */
uint16_t				raw_to_binary_represention(char *raw);

/*
 **				solve.c
 */
void					solve(t_map *map);
t_bool					resolve(t_map *map, int tetrimino, int const size);
t_bool					resolve_plus(t_map *map, int tetrimino, int const size);

/*
 **				dz.c
 */
t_bool					is_enough_space(t_map *map);

/*
 **				print.c
 */
void					print_value_bits(uint16_t value, int sep, int n);
void					print_map(uint16_t map[], int map_size);
void					print_result_map(t_map *map);
void 					print_tetriminos(int toto);
void					print_tetriminos_long(unsigned long toto);
void					print_dyn_map(t_map *map, unsigned int line_size);
void					print_dyn_piece(unsigned __int128 value, unsigned int line_size);

/*
 **				utils.c
 */
int						ft_ceil_sqrt(int n);

/*
 **				error.c
 */
void					fillit_error_msg_exit(char *message);

unsigned __int128		new_form(unsigned __int128  tetriminos, int newline_size);
unsigned __int128		move_to_most_top_left64_position(unsigned __int128 value);

#endif
