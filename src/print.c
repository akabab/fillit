#include "libft.h"
#include "fillit.h"

void		print_map(t_map *map)
{
	int		i;

	while (i < 16)
	{
		print_16bit_representation_of_int(map->m[i], 1);
		i++;
	}
}

void		print_16bit_representation_of_int(uint16_t value, int sep)
{
	uint16_t	mask;
	int			i;

	mask = 0x1 << 15;
	i = 1;
	while (mask > 0)
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