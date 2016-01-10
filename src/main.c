#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "fillit.h"

int			main(int ac, char *av[])
{
	int		fd;
	t_map	map;


	if (ac != 2)
	{
		fillit_error_msg_exit("Usage: ./fillit [map.fillit]");
		return (-1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		fillit_error_msg_exit("some open failed somewhere");
	ft_memset(&map, 0, sizeof(map));
	parse(fd, &map);
	close(fd);
	solve(&map);
	return (0);
}
