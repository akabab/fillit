#include "fillit.h"

static inline t_bool		set_plus(t_map *map, t_tetrimino *t)
{
	unsigned __int128		value;
	int						grid_plus_offset;
	
	t->new_offset = t->offset.y * map->size + t->offset.x;
	value = t->new_value;
	value >>= t->new_offset;
	if (value & map->grid)
		return (FALSE);
	map->grid |= value;
	if (t->new_offset > t->max_grid)
	{
		grid_plus_offset = t->new_offset - 128;
		if (grid_plus_offset > 0)
			value = (t->new_value >> grid_plus_offset);
		else
			value = (t->new_value << grid_plus_offset);
		if (value & map->grid_plus)
			return (FALSE);
		map->grid_plus |= value;

	}
	return (TRUE);
}

static inline void		unset_plus(t_map *map, t_tetrimino *t)
{
	unsigned __int128		value;
	int						grid_plus_offset;

	value = (t->new_value >> t->new_offset);
	map->grid ^= value;
	if (t->new_offset > t->max_grid)
	{
		grid_plus_offset = t->new_offset - 128;
		if (grid_plus_offset > 0)
			value = (t->new_value >> grid_plus_offset);
		else
			value = (t->new_value << grid_plus_offset);
		map->grid_plus ^= value;
	}
}

t_bool		resolve_plus(t_map *map, int tetri_index, int const size)
{
	t_tetrimino		*t;
	t_pos			dyn_pos_backup;

	t = &map->t[tetri_index];
	t->offset = map->dyn_pos[t->pattern_index];
	dyn_pos_backup = map->dyn_pos[t->pattern_index];
	t->offset.x += (t->offset.x > 0) ? t->gap_x : 0;
	while (t->offset.y <= t->max_offset)
	{
		while (t->offset.x <= t->limit_line)
		{
			if (set_plus(map, t))
			{
				map->dyn_pos[t->pattern_index] = t->offset;
				if (((tetri_index + 1 >= map->t_count)
					|| /*(is_enough_space(map) &&*/ resolve(map, tetri_index + 1, size)))
					return (1);
				unset_plus(map, t);
			}
			t->offset.x++;
		}
		t->offset.y += size;
		t->offset.x = 0;
	}
	map->dyn_pos[t->pattern_index] = dyn_pos_backup;
	return (0);
}