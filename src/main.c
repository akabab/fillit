#include "libft.h"
#include "fillit.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h> //

void	test_bit_shifting()
{
	uint16_t	t = -1;
	print_16bit_representation_of_int(t, 4, 4);
}

void	reset_offsets(t_tetrimino t[], int t_count)
{
	int		i;

	i = 0;
	while (i < t_count)
	{
		t[i].offset_x = 0;
		t[i].offset_y = 0;
		++i;
	}
}

int		ft_ceil_sqrt(int n)
{
	int		i;

	i = 0;
	while (i * i < n)
		i++;
	return (i);
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

	// map.t_count = 12;

	// VERIF
	int i = 0;
	while (i < map.t_count)
	{
		printf("%s -> %d, w: %d, h: %d\n", map.t[i].raw, map.t[i].value, map.t[i].width, map.t[i].height);
		i++;
	}

	// RESOLVE
	map.size = ft_ceil_sqrt(map.t_count * 4);
	while (map.size < 16)
	{
		printf("try map of size: %d\n", map.size);
		if (solve(&map, 0))
		{
			// print_map(&map);
			printf("solved with size: %d\n", map.size);
			print_result_map(&map);
			break;
		}
		//reset map & offsets
		ft_bzero(&map.m, sizeof(map.m));
		reset_offsets(map.t, map.t_count);
		map.size++;
	}

	return (0);
}