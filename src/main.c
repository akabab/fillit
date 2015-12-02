#include "libft.h"
#include "fillit.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h> //

int		main(int ac, char *av[])
{
	int				fd;
	t_tetrimino		tetriminos[MAX_TETRIMINOS];
	int				tetriminos_count;

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
	tetriminos_count = parse(fd, tetriminos);
	int i = 0;
	while (i < tetriminos_count)
	{
		printf("%s -> %d\n", tetriminos[i].raw, tetriminos[i].value);
		i++;
	}
	// resolve
	return (0);
}