#include "libft.h"
#include "fillit.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int		main(int ac, char *av[])
{
	int				fd;
	t_map			map;

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
	solve(&map);
	return (0);
}