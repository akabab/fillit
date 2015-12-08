#include "fillit.h"

t_bool		place(t_map *map, t_tetrimino *t)
{
	int			i;
	t_bit_form	tmp_bits;

	// test collision
	// [OPTI] -> inline tests instead of while
	tmp_bits = t->bits;
	tmp_bits.full >>= t->offset_x;
	i = 0;
	while (i < t->height)
	{
		if (tmp_bits.part[i] & map->m[i + t->offset_y])
			return (FALSE);
		i++;
	}
	// pas de collision -> insertion dans la map
	i = 0;
	while (i < t->height)
	{
		map->m[i + t->offset_y] |= tmp_bits.part[i];
		i++;
	}
	return (TRUE);
}

void		reset_position(t_map *map, t_tetrimino *t)
{
	int			i;
	t_bit_form	tmp_bits;

	tmp_bits = t->bits;
	tmp_bits.full >>= t->offset_x;
	i = 0;
	while (i < t->height)
	{
		map->m[i + t->offset_y] &= ~tmp_bits.part[i];
		i++;
	}
}

t_bool		resolve(t_map *map, int tetri_index)
{
	t_tetrimino		*t;
	t_tetrimino		*t_prev;
	t_bool			prev_is_same;

	t = &map->t[tetri_index];
	prev_is_same = (tetri_index > 0 && (t_prev = &map->t[tetri_index - 1]) && t_prev->value == t->value);
	t->offset_y = prev_is_same ? t_prev->offset_y : 0;
	t->offset_x = prev_is_same ? t_prev->offset_x + 1 : 0;
	while (t->offset_y + t->height <= map->size) // pas en buté avec la map en bas
	{
		while (t->offset_x + t->width <= map->size) // pas en buté avec la map a droite
		{
			if (place(map, t))
			{
				// printf("did place at [%d, %d]\n", t->offset_x, t->offset_y);
				// print_map(map);
				if (tetri_index + 1 >= map->t_count)
					return (1);
				if (is_enough_space(map) && resolve(map, tetri_index + 1))
					return (1);
				reset_position(map, t);
				// and reset next tetri offsets
				map->t[tetri_index + 1].offset_x = 0;
				map->t[tetri_index + 1].offset_y = 0;
			}
			t->offset_x++;
		}
		t->offset_y++;
		t->offset_x = 0;
	}
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
	// map->t_count = 11;
	map->space_required = map->t_count * 4;
	map->size = ft_ceil_sqrt(map->space_required);
	// map->size = 8;
	while (map->size < 16)
	{
		map->total_space = map->size * map->size;
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
