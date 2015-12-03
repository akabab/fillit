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
	uint16_t	t = 1 << 1;
	print_16bit_representation_of_int(t);
	t >>= 2;
	print_16bit_representation_of_int(t);
	t <<= 2;
	print_16bit_representation_of_int(t);
}

int		main(int ac, char *av[])
{
	int				fd;
	t_tetrimino		tetriminos[MAX_TETRIMINOS];
	int				tetriminos_count;

	// test_bit_shifting();
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
	tetriminos_count = parse(fd, tetriminos);

	// VERIF
	// int i = 0;
	// while (i < tetriminos_count)
	// {
	// 	printf("%s -> %d\n", tetriminos[i].raw, tetriminos[i].value);
	// 	i++;
	// }

	// RESOLVE
	// ...
	tetriminos[0].offset_x = 3;
	tetriminos[0].offset_y = 1;
	tetriminos[1].offset_x = 1;
	tetriminos[1].offset_y = 2;
	printf("%scollide\n", collide(tetriminos[0], tetriminos[1]) ? "" : "not ");
	return (0);
}