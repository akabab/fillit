#include "fillit.h"

extern const t_pattern		g_patterns[];

t_bool		set(t_map *map, t_tetrimino *t)
{
	uint64_t			value;
	
	value = t->new_value;
	if (t->new_offset <= 31)
	{
		value >>= t->new_offset;
		if (value & map->map1)
			return (FALSE);
		map->map1 |= value;
		map->map2 |= (map->map1 << 31);
	}
	else if (t->new_offset <= 64)
	{
		value >>= (t->new_offset - 32);
		if (value & map->map2)
			return (FALSE);
		map->map2 |= value;
		map->map1 |= (map->map2 >> 32);
		map->map3 |= (map->map2 << 32);
	}
	else
	{
		value >>= (t->new_offset - 64);
		if (value & map->map3)
			return (FALSE);
		map->map3 |= value;
		map->map2 |= (map->map3 >> 32);
	}
	ft_putendl("**** step ****");		
		print_dyn_map(map, map->size);
		print_dyn_piece(value, map->size);
	ft_putendl("**** step ****");		
	return (TRUE);
}

void		unset(t_map *map, t_tetrimino *t)
{
	uint64_t			value;

	value = t->new_value;
	if (t->new_offset <= 32)
	{
		value >>= t->new_offset;
		map->map1 ^= value;
		map->map2 ^= (map->map1 << 32);
	}
	else if (t->new_offset <= 64)
	{
		value >>= (t->new_offset - 32);
		map->map2 ^= value;
		map->map1 ^= (map->map2 >> 32);
		map->map3 ^= (map->map2 << 32);
	}
	else
	{
		value >>= (t->new_offset - 64);
		map->map3 ^= value;
		map->map2 ^= (map->map3 >> 32);
	}
	ft_putchar('\n');
	ft_putendl("**** unset ****");		
		print_dyn_piece(value, map->size);
	ft_putendl("**** unset ****");		
	ft_putchar('\n');
}

t_bool		resolve(t_map *map, int tetri_index)
{
	t_tetrimino		*t;
	int				line_space;
//	int				temp;

	t = &map->t[tetri_index];
//	t->new_offset = map->new_dynpos[t->pattern_index];
//	t->new_offset += (t->offset.x > 0) ? g_patterns[t->pattern_index].gap_x : 0;
//	temp = t->new_offset;
	t->new_offset = 0;
	int i = 0;

	while (i < map->t_count)
	{
		print_dyn_piece(map->t[i].new_value, map->size);
		i++;
	}	
	exit(0);
	while (t->new_offset <= t->max_offset)
	{
		line_space = t->limit_line;
		while (line_space >= 0)
		{
			if (set(map, t))
			{
//				map->new_dynpos[t->pattern_index] = t->new_offset;
				if ((tetri_index + 1 >= map->t_count)
					|| /* (is_enough_space(map) && */resolve(map, tetri_index + 1))
				return (1);
				unset(map, t);
			}
			line_space--;
			t->new_offset++;
		}
		t->new_offset += t->width - 1;
	}
//	map->new_dynpos[t->pattern_index] = temp;
	
	return (0);
}

void		clear(t_map *map)
{
	int		i;

	ft_bzero(map->new_dynpos, sizeof(map->new_dynpos));
	i = 0;
	map->map2 = 0;
	map->map3 = 0;
	while (i < map->t_count)
	{
		map->t[i].new_offset = 0;
		map->t[i].new_value = move_to_most_top_left64_position(map->t[i].value);
		print_tetriminos(map->t[i].value);
		map->t[i].new_value = new_form(map->t[i].new_value, 8);
		print_dyn_piece(map->t[i].new_value, 8);
		map->t[i].max_offset = map->total_space
			- (map->t[i].height * map->size);
		map->t[i].limit_line = map->size - map->t[i].width;
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
			print_dyn_map(map, map->size);
			break ;
		}
		map->size++;
	}
}
