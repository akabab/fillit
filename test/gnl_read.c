#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "libft.h"

int		main(int ac, char *av[])
{
	int		fd;
	int		size;
	char	*line;
	int		ret;
	int		count;

	if (ac != 3)
		return printf("Usage: ./a.out [file] [BUFFER_SIZE]\n");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return printf("Open failed\n");
	if (!(size = atoi(av[2])))
		return printf("error on atoi\n");

	#define BUFF_SIZE size

	line = NULL;
	count = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ret == -1)
			return printf("error reading..\n");
		count += strlen(line) + 1;
	}
	printf("did read %d chars\n", count);
	return (0);
}