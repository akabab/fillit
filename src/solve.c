#include "fillit.h"

extern const t_pattern		g_patterns[];

t_bool		set(t_map *map, t_tetrimino *t)
{
	int			i;
	t_bit_form	tmp_bits;

	tmp_bits = t->bits;
	tmp_bits.full >>= t->offset.x;
	i = 0;
	while (i < t->height)
	{
		if (tmp_bits.part[i] & map->m[i + t->offset.y])
			return (FALSE);
		i++;
	}
	i = 0;
	while (i < t->height)
	{
		map->m[i + t->offset.y] |= tmp_bits.part[i];
		i++;
	}
	return (TRUE);
}

void		unset(t_map *map, t_tetrimino *t)
{
	int			i;
	t_bit_form	tmp_bits;

	tmp_bits = t->bits;
	tmp_bits.full >>= t->offset.x;
	i = 0;
	while (i < t->height)
	{
		map->m[i + t->offset.y] &= ~tmp_bits.part[i];
		i++;
	}
}

t_bool		resolve(t_map *map, int tetri_index)
{
	t_tetrimino		*t;
	t_pos			dyn_pos_backup;

	t = &map->t[tetri_index];
	t->offset = dyn_pos_backup = map->dyn_pos[t->pattern_index];
	t->offset.x += (t->offset.x > 0) ? g_patterns[t->pattern_index].gap_x : 0;
	while (t->offset.y + t->height <= map->size)
	{
		while (t->offset.x + t->width <= map->size)
		{
			if (set(map, t))
			{
				map->dyn_pos[t->pattern_index] = t->offset;
				if ((tetri_index + 1 >= map->t_count)
					|| (/*is_enough_space(map) && */resolve(map, tetri_index + 1)))
					return (1);
				unset(map, t);
			}
			t->offset.x++;
		}
		t->offset.y++;
		t->offset.x = 0;
	}
	map->dyn_pos[t->pattern_index] = dyn_pos_backup;
	return (0);
}

void		clear(t_map *map)
{
	int		i;

	ft_bzero(map->m, sizeof(map->m));
	ft_bzero(map->mdz, sizeof(map->mdz));
	ft_bzero(map->dyn_pos, sizeof(map->dyn_pos));
	i = 0;
	while (i < map->t_count)
	{
		map->t[i].offset.x = 0;
		map->t[i].offset.y = 0;
		i++;
	}
}

void		solve(t_map *map)
{
	map->space_required = map->t_count * 4;
	map->size = ft_ceil_sqrt(map->space_required);
	while (map->size < 16)
	{
		clear(map);
		map->total_space = map->size * map->size;
		if (resolve(map, 0))
		{
			print_result_map(map);
			break ;
		}
		map->size++;
	}
}
