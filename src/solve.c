#include "fillit.h"

t_bool		place(t_map *map, t_tetrimino *t)
{
	int			i;
	uint16_t	tmp_v[4];

	// test collision
	// [OPTI] -> inline tests instead of while
	i = 0;
	while (i < t->height) // [OPTI] -> test only for i < t->height
	{
		tmp_v[i] = t->v[i] >> t->offset_x;
		if (tmp_v[i] & map->m[i + t->offset_y])
		{
			return (FALSE);
		}
		i++;
	}
	// pas de collision -> insertion dans la map
	i = 0;
	while (i < t->height)
	{
		map->m[i + t->offset_y] |= tmp_v[i];
		i++;
	}
	return (TRUE);
}

void		reset_position(t_map *map, t_tetrimino *t)
{
	int			i;
	uint16_t	tmp_v[4];

	i = 0;
	while (i < t->height)
	{
		tmp_v[i] = t->v[i] >> t->offset_x;
		map->m[i + t->offset_y] &= ~tmp_v[i];
		i++;
	}
}

t_bool		resolve(t_map *map, int tetri_index)
{
	t_tetrimino		*t;

	if (tetri_index > map->t_count - 1) // all placés
	{
		// printf("did place all tetris\n");
		return (1);
	}
	// printf("solve call: [%d]\n", tetri_index);
	t = &map->t[tetri_index];
	while (t->offset_y + t->height <= map->size) // pas en buté avec la map en bas
	{
		t->offset_x = 0;
		while (t->offset_x + t->width <= map->size) // pas en buté avec la map a droite
		{
			if (place(map, t))
			{
				// printf("did place at [%d, %d]\n", t->offset_x, t->offset_y);
				// print_map(map);
				if (resolve(map, tetri_index + 1))
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
	// printf("could not place tetri [%d]\n", tetri_index);
	return (0);
}

void		reset_tetri_offsets(t_tetrimino t[], int t_count)
{
	int		i;

	i = 0;
	while (i < t_count)
	{
		t[i].offset_x = 0;
		t[i].offset_y = 0;
		i++;
	}
}

void		solve(t_map *map)
{
	map->size = ft_ceil_sqrt(map->t_count * 4);
	while (map->size < 16)
	{
		printf("try map of size: %d\n", map->size);
		if (resolve(map, 0))
		{
			printf("solved with size: %d\n", map->size);
			print_result_map(map);
			break;
		}
		//reset map & offsets
		ft_bzero(map->m, sizeof(map->m));
		reset_tetri_offsets(map->t, map->t_count);
		map->size++;
	}
}