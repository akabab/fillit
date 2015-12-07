#include "libft.h"
#include "fillit.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int		get_bit_from_int(uint16_t value, int n)
{
	return ((value >> n) & 0x1);
}

int		main(int ac, char *av[])
{
	int				fd;
	t_map			map;

	printf("%d\n", get_bit_from_int(4, 1));
	return (1);
	if (ac != 2)
	{
		ft_printf("Usage: %s [map.fillit]\n", av[0]);
		return (-1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error_msg_exit(NULL);
	ft_memset(&map, 0, sizeof(map));
	map.t_count = parse(fd, map.t);
	close(fd);
	solve(&map);
	return (0);
}