#include "fillit.h"

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

void try_next(t_tetrimino *tetriminos, int current)
{
	//mettre dans int 
}

