#include "libft.h"
#include "fillit.h"

void			print_map(uint16_t map[], int map_size)
{
	int				i;

	i = 0;
	while (i < map_size)
	{
		print_value_bits(map[i], 1, map_size);
		i++;
	}
}

void			print_value_bits(uint16_t value, int sep, int n)
{
	uint16_t		mask;
	int				i;

	mask = 0x1 << 15;
	i = 1;
	while (mask > 0 && n--)
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

static void		write_t(char *r_map, int map_size,
		t_tetrimino *t, int t_index)
{
	int				i;
	int				j;
	uint16_t		tmp_val;
	int				index;

	i = 0;
	tmp_val = t->value;
	while (i < 16)
	{
		j = 0;
		while (j < 4)
		{
			if (tmp_val & (0x1 << 15))
			{
				t->offset.x = t->new_offset % map_size;
				t->offset.y = t->new_offset / map_size;
				index = (t->offset.y + i) * (map_size + 1) + (t->offset.x + j);
				r_map[index] = 'A' + t_index;
			}
			tmp_val <<= 1;
			j++;
		}
		i++;
	}
}

void			print_result_map(t_map *map)
{
	int				i;
	int				tetri_index;
	char			*r_map;
	int				r_map_size;

	r_map_size = (map->size + 1) * map->size;
	r_map = (char *)ft_strnew(r_map_size * sizeof(char));
	if (!r_map)
		return (fillit_error_msg_exit(NULL));
	ft_memset(r_map, '.', r_map_size);
	i = 0;
	while (i < map->size)
	{
		r_map[(i + 1) * (map->size + 1) - 1] = '\n';
		i++;
	}
	tetri_index = 0;
	while (tetri_index < map->t_count)
	{
		write_t(r_map, map->size, &map->t[tetri_index], tetri_index);
		tetri_index++;
	}
	ft_putstr(r_map);
	ft_strdel(&r_map);
}
