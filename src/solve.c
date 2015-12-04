#include "fillit.h"

t_bool		place(t_map *map, t_tetrimino *t)
{
	int			i;
	uint16_t	tmp_v[4];

	// test collision
	i = 0;
	while (i < 4) // [OPTI] -> test only for i < t->height
	{
		tmp_v[i] = t->v[i] >> t->offset_x;
		if (tmp_v[i] & map->m[i + t->offset_y])
		{
			// printf("collide at [%d, %d]\n", t->offset_x, t->offset_y);
			// ft_putstr("val: ");
			// print_16bit_representation_of_int(t->v[i], 0);
			// ft_putstr("map: ");
			// print_16bit_representation_of_int(map->m[i + t->offset_y], 0);
			return (FALSE);
		}
		i++;
	}
	// pas de collision -> insertion dans la map
	printf("no collision\n");
	i = 0;
	while (i < 4)
	{
		// printf("tmp_v[%d] = %d\n", i, tmp_v[i]);
		map->m[i + t->offset_y] |= tmp_v[i];
		// print_map(map);
		i++;
	}
	// print_map(map);
	return (TRUE);
}

void		reset_position(t_map *map, t_tetrimino *t)
{
	int			i;
	uint16_t	tmp_v[4];

	printf("before reset\n");
	print_map(map);
	i = 0;
	while (i < 4) // t->height
	{
		tmp_v[i] = t->v[i] >> t->offset_x;
		map->m[i + t->offset_y] &= ~tmp_v[i];
		++i;
	}
	printf("after reset\n");
	print_map(map);
}

t_bool		solve(t_map *map, int tetri_index)
{
	t_tetrimino		*t;

	if (tetri_index > map->t_count - 1) // all placés
	{
		printf("did place all tetris\n");
		return (1);
	}
	printf("solve call: [%d]\n", tetri_index);
	t = &map->t[tetri_index];
	while (t->offset_y + t->height <= map->size) // pas en buté avec la map en bas
	{
		t->offset_x = 0;
		while (t->offset_x + t->width <= map->size) // pas en buté avec la map a droite
		{
			if (place(map, t))
			{
				printf("did place at [%d, %d]\n", t->offset_x, t->offset_y);
				print_map(map);
				if (solve(map, tetri_index + 1))
					return (1);
				reset_position(map, t);
				// and reset next tetri offsets
				map->t[tetri_index + 1].offset_x = 0;
				map->t[tetri_index + 1].offset_y = 0;
			}
			t->offset_x++;
		}
		t->offset_y++;
	}
	printf("could not place tetri [%d]\n", tetri_index);
	return (0);
}