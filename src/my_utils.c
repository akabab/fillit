#include "fillit.h"
#include <stdio.h>
#include <stdint.h>

void print_tetriminos_long(unsigned long toto);

int64_t		move_to_most_top_left64_position(uint64_t value)
{
	// move to most left position
	while ((value & LEFT_MASK64) == 0)
	{
		// printf("move right\n");
		value <<= 1;
	}
	// move to most top position
	while ((value & TOP_MASK64) == 0)
	{
		value <<= 8;
	}
	// printf("value = %d\n", value);
	// print_16bit_representation_of_int(value);
	return (value);
}

int		print_dyn_map(uint64_t map, unsigned int line_size)
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
	return (1);
}

uint64_t		new_form(uint64_t tetriminos, int newline_size)
{
	uint64_t	mask;
	uint64_t	result;
	int	count;

	//change le sens
	mask = 0xF000000000000000;
	result = 0;
	count = 0;
	while (count < 4)
	{
		result |= ((mask & tetriminos)
				>> (newline_size - 4) * count);	
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
