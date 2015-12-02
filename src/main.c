#include "libft.h"
#include "fillit.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	get_binary_represention(t_tetrimino tetrimino)
{
	char	*raw;
	int		i;

	tetrimino.value = 0x0000;
	i = 0xF;
	raw = tetrimino.raw;
	ft_printf("raw: %s\n", raw);
	while (*raw)
	{
		// try [OPTI -> cast (int) move 4 by 4]

		if (*raw == CHAR_BLOCK)
		{
			tetrimino.value |= 1 << i;
			tetrimino.bi_value |= 1 << ( i / 4);

		}
		else if (*raw != CHAR_EMPTY)
		{
			// handle error
			ft_printf("invalid char: %c\n", *raw);
			return;
		}
		raw++;
		i--;
	}
	ft_printf("value: %d\n", tetrimino.value);
	// move tetrimino to most top-left position
}

int		parse_tetrimino(fd)
{
	char			*line;
	int				ret;
	int				line_index;
	static	char	index = 'A';

	t_tetrimino		tetrimino;
	tetrimino.raw = ft_strnew(16);

	line = NULL;
	line_index = 0;
	while (line_index < 4) // 4 lines to be read
	{
		ret = get_next_line(fd, &line); // try [OPTI -> BUFFER_SIZE = 5]

		// handle ret error or eof
		if (ret == -1)
			return (-1);
		if (ret == 0)
			return (0);

		// handle line length error
		if (ft_strlen(line) != 4) // try [OPTI -> implementation of ft_strlen]
			return (-1);

		ft_strcpy(tetrimino.raw + (line_index * 4), line);

		// ft_putendl(line);
		// save tetromino
		line_index++;
	}
	get_binary_represention(tetrimino);
	// check next line to see if it continues
	get_next_line(fd, &line);
	return (ret);
}

int		parse(int fd)
{
	t_tetrimino		tetriminos[26];

	while (parse_tetrimino(fd))
	{

	}
	return (0);
}

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
	parse(fd);
	return (0);
}
