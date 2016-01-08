#include "fillit.h"
#include <stdio.h>
#include <stdint.h>

int64_t		move_to_most_top_left64_position(uint64_t value)
{
	while ((value & LEFT_MASK64) == 0)
	{
		value <<= 1;
	}
	while ((value & TOP_MASK64) == 0)
	{
		value <<= 8;
	}
	return (value);
}

void			print_dyn_map(uint64_t map, unsigned int line_size)
{
	uint64_t 	mask;
	int			end_map;

	mask = 0x1;
	mask <<= 63;
	end_map = line_size * line_size;
	while (end_map)
	{
		ft_putchar(((map & mask) ? '#': '.'));
		mask >>= 1;
		if ((end_map - 1) % (line_size) == 0)
			ft_putchar('\n');
		end_map--;
	}
	ft_putchar('\n');
}

uint64_t		new_form(uint64_t tetriminos, int newline_size)
{
	uint64_t	mask;
	uint64_t	result;
	int			count;
	int			diff;

	mask = 0xF000000000000000;
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

