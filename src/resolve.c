#include "fillit.h"

extern const t_pattern		g_patterns[];

static inline t_bool		set(t_map *map, t_tetrimino *t)
{
	unsigned __int128		value;

	t->new_offset = t->offset.y + t->offset.x;
	value = (t->new_value >> t->new_offset);
	if (value & map->grid)
		return (FALSE);
	map->grid |= value;
	return (TRUE);
}

static inline void			unset(t_map *map, t_tetrimino *t)
{
	unsigned __int128		value;

	value = (t->new_value >> t->new_offset);
	map->grid ^= value;
}

t_bool						resolve(t_map *map, int tetri_index, int const size)
{
	t_tetrimino				*t;
	t_pos					dyn_pos_backup;

	t = &map->t[tetri_index];
	t->offset = map->dyn_pos[t->pattern_index];
	dyn_pos_backup = map->dyn_pos[t->pattern_index];
	t->offset.x += (t->offset.x > 0) ? g_patterns[t->pattern_index].gap_x : 0;
	while (t->offset.y <= t->max_offset)
	{
		while (t->offset.x <= t-> limit_line)
		{
			if (set(map, t))
			{
				map->dyn_pos[t->pattern_index] = t->offset;
				if (((tetri_index + 1 >= map->t_count)
					|| resolve(map, tetri_index + 1, size)))
					return (1);
				unset(map, t);
			}
			t->offset.x++;
		}
		t->offset.y += size;
		t->offset.x = 0;
	}
	map->dyn_pos[t->pattern_index] = dyn_pos_backup;
	return (0);
}
