#include "fillit.h"

extern const t_pattern		g_patterns[];

t_bool		set(t_map *map, t_tetrimino *t)
{
	int			value;

	value = t->new_value;
	value >>= t->new_offset;
	if (value & map->map1)
		return (FALSE);
	map->map1 |= value;
	print_tetriminos_long(value);
	return (TRUE);
}

void		unset(t_map *map, t_tetrimino *t)
{
	int			value;

	value = t->new_value;
	value >>= t->new_offset;
	map->map1 ^= value;
}

t_bool		resolve(t_map *map, int tetri_index)
{
	t_tetrimino		*t;
//	int				temp;

	t = &map->t[tetri_index];
//	t->new_offset = map->new_dynpos[t->pattern_index];
//	t->new_offset += (t->offset.x > 0) ? g_patterns[t->pattern_index].gap_x : 0;
//	temp = t->new_offset;
	t->new_offset = 0;
	while (t->new_offset <= t->max_offset)
	{
		if (set(map, t))
		{
//			map->new_dynpos[t->pattern_index] = t->new_offset;
			if ((tetri_index + 1 >= map->t_count)
				|| /* (is_enough_space(map) && */resolve(map, tetri_index + 1))
				return (1);
			unset(map, t);
		}
		t->new_offset++;
	}
//	map->new_dynpos[t->pattern_index] = temp;
	return (0);
}

void		clear(t_map *map)
{
	int		i;

	ft_bzero(map->dyn_pos, sizeof(map->dyn_pos));
	ft_bzero(map->new_dynpos, sizeof(map->new_dynpos));
	i = 0;
	map->map1 = 0;
	map->map2 = 0;
	map->map3 = 0;
	while (i < map->t_count)
	{
		map->t[i].new_offset = 0;
		map->t[i].new_value = move_to_most_top_left64_position(map->t[i].value);
		map->t[i].new_value = new_form(map->t[i].new_value, 2);
		print_tetriminos_long(map->t[i].new_value);
		map->t[i].max_offset = map->total_space
			- (map->t[i].height * map->size);
		i++;
	}
	exit(0);
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
			print_tetriminos_long(map->map1);
			break ;
		}
		map->size++;
	}
}
