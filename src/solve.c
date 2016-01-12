#include "fillit.h"

extern const t_pattern		g_patterns[];

t_bool		set_plus(t_map *map, t_tetrimino *t)
{
	unsigned __int128		value;

	t->new_offset = t->offset.y * map->size + t->offset.x;
	value = t->new_value;
	value >>= t->new_offset;
	if (value & map->grid)
		return (FALSE);
	map->grid |= value;
	if (t->new_offset > t->max_grid)
	{
		t->grid_plus_offset = t->new_offset - 128;
		if (t->grid_plus_offset > 0)
			value = (t->new_value >> t->grid_plus_offset);
		else
			value = (t->new_value << t->grid_plus_offset);
		if (value & map->grid_plus)
			return (FALSE);
		map->grid_plus |= value;

	}
	return (TRUE);
}


t_bool		set(t_map *map, t_tetrimino *t)
{
	unsigned __int128		value;

	t->new_offset = t->offset.y * map->size + t->offset.x;
	value = t->new_value;
	value >>= t->new_offset;
	if (value & map->grid)
		return (FALSE);
	map->grid |= value;
	return (TRUE);
}

void		unset_plus(t_map *map, t_tetrimino *t)
{
	unsigned __int128		value;

	value = t->new_value;
	value >>= (t->new_offset);
	map->grid ^= value;
	if (t->new_offset > t->max_grid)
	{
		t->grid_plus_offset = t->new_offset - 128;
		if (t->grid_plus_offset > 0)
			value = (t->new_value >> t->grid_plus_offset);
		else
			value = (t->new_value << t->grid_plus_offset);
		map->grid_plus ^= value;
	}
}

void		unset(t_map *map, t_tetrimino *t)
{
	unsigned __int128		value;

	value = t->new_value;
	value >>= (t->new_offset);
	map->grid ^= value;
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
			if (map->set(map, t))
			{
				map->dyn_pos[t->pattern_index] = t->offset;
				if (((tetri_index + 1 >= map->t_count)
					|| /*(is_enough_space(map) &&*/ resolve(map, tetri_index + 1)))
					return (1);
				map->unset(map, t);
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

	i = 0;
	ft_bzero(map->dyn_pos, sizeof(map->dyn_pos));
	map->set = (map->size < 12) ? set : set_plus;
	map->unset = (map->size < 12) ? unset : unset_plus;
	map->grid = 0;
	map->grid_plus = 0;
	while (i < map->t_count)
	{
		map->t[i].offset.x = 0;
		map->t[i].offset.y = 0;
		map->t[i].new_value = move_to_most_top_left64_position(map->t[i].value);
		map->t[i].new_value = new_form(map->t[i].new_value, map->size);
		map->t[i].max_offset = map->total_space
			- (map->t[i].height * map->size);
		map->t[i].max_grid = 128 - (map->t[i].height * map->size);
		map->t[i].limit_line = map->size - map->t[i].width;
		i++;
	}
}

void		solve(t_map *map)
{
	map->space_required = map->t_count * 4;
	map->size = ft_ceil_sqrt(map->space_required);
	while (map->size < 16)
	{
		map->total_space = map->size * map->size;
		clear(map);
		if (resolve(map, 0))
		{
			print_result_map(map);
			break ;
		}
		map->size++;
	}
}
