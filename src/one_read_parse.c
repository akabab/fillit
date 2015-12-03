
int		one_read_parsing(int fd)
{
	t_tetrimino		tetriminos[26] = {0}; // not sure I'm allowed to init here
	char			buffer[BUFFER_SIZE + 1];
	int				char_count;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	ft_printf("Reading [0-%d] chars...\n", BUFFER_SIZE);
	char_count = read(fd, buffer, BUFFER_SIZE);
	if (char_count == -1)
	{
		// handle error
		ft_putendl("read error");
		ft_perror(NULL);
		return (0);
	}
	if (char_count == 0)
	{
		// empty file ?
		ft_putendl("nothing to read");
		return (0);
	}
	ft_printf("did read %d chars\n", char_count);
	if (char_count >= BUFFER_SIZE)
	{
		// handle error
		ft_printf("too much chars read -> %d\n", char_count);
		return (0);
	}
	if ((char_count + 1) % (MAX_TETRIMINO_SIZE + 1))
	{
		ft_putendl("invalid char count read");
		return (0);
	}
	ft_putendl("Parsing OK");


	// PARSE TETRIMINOS
	int		i;
	char	*ptr;
	char	*tetrimino_unparsed;
	
	ptr = buffer;
	i = 0;
	while (i < char_count)
	{
		int j = 0;
		tetrimino_unparsed = buffer + i;
		while (j < MAX_TETRIMINO_SIZE)
		{
			if (j % 5 == 0 && tetrimino_unparsed[j] != '\n')
			{
				ft_putendl("invalid: should be a \\n");
				// undone
				return (-1);
			}
			j++;
		}
		i += j;
	}
	return (0);
}