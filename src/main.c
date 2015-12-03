#include "libft.h"
#include "fillit.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h> //

// [OPTI] -> by ref instead of copy ( is struct copied ? )
t_bool	collide(t_tetrimino tetri_a, uint64_t *buffer)
{
	uint64_t 		ret;
	uint64_t		tmp_b_value;
	uint64_t		temp;

	temp = *buffer;
	tmp_b_value = tetri_a.value;
	print_tetriminos(tetri_a.value);
	print_tetriminos_long(*buffer);
	print_tetriminos_long(tmp_b_value);
	print_tetriminos_long(temp |= tmp_b_value);
	ret = (temp ^ tmp_b_value);
	print_tetriminos_long(ret);
	if (ret == *buffer)
	{
		*buffer = temp;
		print_tetriminos(*buffer);
		return (TRUE);
	}
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
	uint64_t			buffer;

	// test_bit_shifting();
	buffer = 0;
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
/*	tetriminos[0].offset_x = 3;
	tetriminos[0].offset_y = 1;
	tetriminos[1].offset_x = 1;
	tetriminos[1].offset_y = 2;
	while(!collide(tetriminos[0], &buffer))
	{
		tetriminos[0].offset_x += 2;
	}
	while(!collide(tetriminos[1], &buffer))
	{
		uint64_t temp2 = move(tetriminos[1].value, 2);
		tetriminos[1].value = temp2;
	}
	while(!collide(tetriminos[1], &buffer))
	{
		uint64_t temp2 = move(tetriminos[1].value, 1);
		tetriminos[1].value = temp2;
	}
	while(!collide(tetriminos[0], &buffer))
	{
		uint64_t temp2 = move(tetriminos[0].value, 1);
		tetriminos[1].value = temp2;
	}

//	
//	printf("%scollide\n", collide(tetriminos[0], tetriminos[1]) ? "" : "not ");
	*/
	return (0);
}
