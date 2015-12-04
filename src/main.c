#include "libft.h"
#include "fillit.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h> //

// [OPTI] -> by ref instead of copy ( is struct copied ? )
t_bool	collide(t_tetrimino tetri_a, t_tetrimino tetri_b)
{
	// uint16_t	tmp_a_value;
	uint16_t	tmp_b_value;
	int			delta_x;
	int			delta_y;

	delta_x = tetri_b.offset_x - tetri_a.offset_x;
	delta_y = tetri_b.offset_y - tetri_a.offset_y;
	if (ft_abs(delta_x) >= 4 || ft_abs(delta_y) >= 4)
		return (FALSE);
	// clusterize
	tmp_b_value = move(tetri_b.value, delta_x + (delta_y * 4));
	if (tetri_a.value & tmp_b_value)
		return (TRUE);
	return (FALSE);
}

void	test_bit_shifting()
{
	uint16_t	t = -1;
	print_16bit_representation_of_int(t);
}

int		main(int ac, char *av[])
{
	int				fd;
	t_map			map = {0};

	// test_bit_shifting(); return (-1);
	if (ac != 2)
	{
		ft_printf("Usage..\n");
		return (-1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Open failed\n");
		return (-1);
	}
	// PARSE
	map.t_count = parse(fd, map.t);

	// VERIF
	// int i = 0;
	// while (i < map.t_count)
	// {
	// 	printf("%s -> %d\n", map.t[i].raw, map.t[i].value);
	// 	i++;
	// }

	// RESOLVE
	// ...
	return (0);
}