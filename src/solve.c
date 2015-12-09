#include "fillit.h"

t_bool		set(t_map *map, t_tetrimino *t)
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

void		unset(t_map *map, t_tetrimino *t)
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

	t = &map->t[tetri_index];
	t->offset_x = map->dyn_pos[t->pattern_index].x; // [OPTI] + t->width if (dyn_pos.x != 0)
	t->offset_y = map->dyn_pos[t->pattern_index].y;
	while (t->offset_y + t->height <= map->size) // pas en buté avec la map en bas
	{
		while (t->offset_x + t->width <= map->size) // pas en buté avec la map a droite
		{
			if (set(map, t))
			{
				map->dyn_pos[t->pattern_index].x = t->offset_x;
				map->dyn_pos[t->pattern_index].y = t->offset_y;
				if (tetri_index + 1 >= map->t_count)
					return (1);
				if (is_enough_space(map) && resolve(map, tetri_index + 1))
					return (1);
				unset(map, t);
			}
			t->offset_x++;
		}
		t->offset_y++;
		t->offset_x = 0;
	}
	map->dyn_pos[t->pattern_index].x = 0;
	map->dyn_pos[t->pattern_index].y = 0;
	return (0);
}

void		clear(t_map *map)
{
	int		i;

	ft_bzero(map->m, sizeof(map->m));
	ft_bzero(map->mdz, sizeof(map->mdz)); // quite useless but w/e
	ft_bzero(map->dyn_pos, sizeof(map->dyn_pos));
	i = 0;
	while (i < map->t_count)
	{
		map->t[i].offset_x = 0;
		map->t[i].offset_y = 0;
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
		clear(map);
		map->total_space = map->size * map->size;
		printf("try map of size: %d\n", map->size);
		if (resolve(map, 0))
		{
			printf("solved with size: %d\n", map->size);
			print_result_map(map);
			break;
		}
		map->size++;
	}
}
