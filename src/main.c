#include "libft.h"
#include "fillit.h"
#include <fcntl.h>

int		main(int ac, char *av[])
{
	int		fd;
	
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
	return (0);
}