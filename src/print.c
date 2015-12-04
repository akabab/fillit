#include "libft.h"
#include "fillit.h"

void		print_map(t_map *map)
{
	int		i;

	while (i < map->size)
	{
		print_16bit_representation_of_int(map->m[i], 1, map->size);
		i++;
	}
}

void		print_16bit_representation_of_int(uint16_t value, int sep, int limit)
{
	uint16_t	mask;
	int			i;

	mask = 0x1 << 15;
	i = 1;
	while (mask > 0 && limit--)
	{
		if (value & mask)
			ft_putchar('1');
		else
			ft_putchar('0');
		if (sep && (i % sep) == 0)
			ft_putchar(' ');
		mask >>= 1;
		i++;
	}
	ft_putchar('\n');
}

void		write_treti_in_result_map(char *r_map, int map_size, t_tetrimino *t, int tetri_index)
{
	int				i;
	int				j;
	uint16_t		mask;
	uint16_t		val;

	mask = 0x1 << 15;
	i = 0;
	while (i < t->height) // t->height
	{
		j = 0;
		val = t->v[i];
		while (j < t->width) // t->width
		{
			if (val & mask)
				r_map[(t->offset_y + i) * (map_size + 1) + (t->offset_x + j)] = 'A' + tetri_index;
			val <<= 1;
			++j;
		}
		++i;
	}
}

void		print_result_map(t_map *map)
{
	int				i;
	int				tetri_index;
	char			*r_map;
	int				r_map_size;

	r_map_size = (map->size + 1) * map->size;
	r_map = (char *)ft_strnew(r_map_size * sizeof(char));
	if (!r_map)
		error_msg_exit(NULL);
	ft_memset(r_map, '.', r_map_size);
	i = 0;
	while (i < map->size)
	{
		r_map[(i + 1) * (map->size + 1) - 1] = '\n';
		++i;
	}
	tetri_index = 0;
	while (tetri_index < map->t_count)
	{
		write_treti_in_result_map(r_map, map->size, &map->t[tetri_index], tetri_index);
		++tetri_index;
	}
	ft_putstr(r_map);
}