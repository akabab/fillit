#include "fillit.h"
#include <stdio.h>
#include <stdint.h>

void			print_dyn_piece(unsigned __int128 value, unsigned int line_size)
{
	unsigned __int128 	mask;
	int					end_map;

	mask = 0x1;
	mask <<= 127;
	end_map = line_size * line_size;
	while (end_map && mask)
	{
		ft_putchar(((value & mask) ? '#': '.'));
		mask >>= 1;
		if ((end_map - 1) % (line_size) == 0)
			ft_putchar('\n');
		end_map--;
	}
	mask <<= 127;
	while (end_map)
	{
		ft_putchar('.');
		if ((end_map - 1) % (line_size) == 0)
			ft_putchar('\n');
		end_map--;
	}
	ft_putchar('\n');
}

unsigned __int128		move_to_most_top_left64_position(unsigned __int128 value)
{
	value <<= 112;
	return (value);
}

void			print_dyn_map(t_map *map, unsigned int line_size)
{
	unsigned __int128 	mask;
	int					end_map;

	mask = 0x1;
	mask <<= 127;
	end_map = line_size * line_size;
	while (end_map && mask)
	{
		ft_putchar(((map->grid & mask) ? '#': '.'));
		mask >>= 1;
		if ((end_map - 1) % (line_size) == 0)
			ft_putchar('\n');
		end_map--;
	}
	ft_putchar('\n');
}


unsigned __int128		new_form(unsigned __int128 tetriminos, int newline_size)
{
	unsigned __int128	mask;
	unsigned __int128	result;
	int					count;
	int					diff;

	mask = 0xF;
	mask <<= 124;
	result = 0;
	count = 0;
	diff = newline_size - 4;
	while (count < 4)
	{
		if (diff > 0)
			result |= ((mask & tetriminos)
					>> diff * count);
		else if (diff < 0)
			result |= ((mask & tetriminos)
					<< (-diff) * count);
		else
			result |= (mask & tetriminos);
		mask >>= 4;
		count++;
	}
	return (result);
}

void print_tetriminos(int toto)
{
	int i = 0;
	int mask = 1 << 15;

	while (mask)
	{
		ft_putchar((mask & toto) ? '#' : '.');	
		mask >>= 1;
		i++;
		if (i % 4 == 0)
			ft_putchar('\n');	
	}
	ft_putchar('\n');
}

void print_tetriminos_long(unsigned long toto)
{
	int i = 0;
	uint64_t  mask = 0x1;

	mask <<= 63;
	while (mask != 0)
	{
		ft_putchar((mask & toto) ? '#' : '.');	
		mask >>= 1;
		i++;
		if (i % 8 == 0)
			ft_putchar('\n');	
	}
	ft_putchar('\n');
}

