#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int		main(int ac, char *av[])
{
	int		fd;
	int		size;
	char	*buffer;
	int		ret;

	if (ac != 3)
		return printf("Usage: ./a.out [file] [BUFFER_SIZE]\n");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return printf("Open failed\n");
	if (!(size = atoi(av[2])))
		return printf("error on atoi\n");
	if (!(buffer = (char *)malloc((size + 1) * sizeof(char))))
		return printf("error malloc\n");
	bzero(buffer, size + 1);
	ret = read(fd, buffer, size);
	printf("did read %d chars\n", ret);
	return (0);
}