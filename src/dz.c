#include "fillit.h"

static int		count_adj(t_map *map, int x, int y)
{
	uint16_t	tmp_value;
	uint16_t	bit;
	int			adj_sum;

	if (x < 0 || x >= map->size || y < 0 || y >= map->size)
		return (0);
	tmp_value = map->mdz[y];
	bit = (tmp_value >> (0xF - x)) & 0x1;
	if (bit)
		return (0);
	map->mdz[y] |= 0x8000 >> x;
	adj_sum = 1;
	adj_sum += count_adj(map, x - 1, y);
	adj_sum += count_adj(map, x, y - 1);
	adj_sum += count_adj(map, x + 1, y);
	adj_sum += count_adj(map, x, y + 1);
	return (adj_sum);
}

t_bool			is_enough_space(t_map *map)
{
	int			n_dz;
	int			x;
	int			y;
	int			adj;

	ft_memcpy(map->mdz, map->m, sizeof(map->m));
	n_dz = 0;
	y = 0;
	while (y < map->size)
	{
		x = 0;
		while (x < map->size)
		{
			adj = count_adj(map, x, y);
			if (adj < 4)
				n_dz += adj;
			if (map->total_space - n_dz < map->space_required)
				return (FALSE);
			x++;
		}
		y++;
	}
	return (TRUE);
}
