#include <unistd.h>
#include "libft.h"
#include "fillit.h"

int				get_pattern(uint16_t value)
{
	int						i;
	static const uint16_t	patterns[TETRI_PATTERNS_COUNT] = {
		57856, 17600, 36352, 51328, 58368, 19520, 19968, 35968,
		59392, 50240, 11776, 35008, 27648, 35904, 61440, 34952,
		52224, 50688, 19584
	};

	i = 0;
	while (i < TETRI_PATTERNS_COUNT)
	{
		if (value == patterns[i])
			return (i);
		i++;
	}
	return (-1);
}

uint16_t		move_to_most_top_left_position(uint16_t value)
{
	while ((value & LEFT_MASK) == 0)
		value <<= 1;
	while ((value & TOP_MASK) == 0)
		value <<= 4;
	return (value);
}

uint16_t		raw_to_binary_represention(char *raw)
{
	int			i;
	uint16_t	value;

	value = 0x0000;
	i = 0xF;
	while (*raw)
	{
		if (*raw == CHAR_BLOCK)
			value |= 1 << i;
		raw++;
		i--;
	}
	value = move_to_most_top_left_position(value);
	return (value);
}

int			get_width(uint16_t v)
{
	int		width;

	width = 4;
	while (width && !(v & 0x1000))
	{
		v >>= 1;
		width--;
	}
	return (width);
}

void		set_v(t_tetrimino *t)
{
	int			i;
	uint16_t	mask;

	mask = 0xF000;
	i = 0;
	while (i < 4)
	{
		t->bits.part[i] = (t->value & mask) << (i * 4);
		if (t->bits.part[i])
		{
			t->height++;
			t->width = ft_max(t->width, get_width(t->bits.part[i]));
		}
		mask >>= 4;
		++i;
	}
}

int			read_input(int fd, char *buffer)
{
	int		char_count;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	char_count = read(fd, buffer, BUFFER_SIZE);
	if (char_count == -1)
		error_msg_exit("read failed");
	return (char_count);
}

void		prepare_entry_for_split(char *input_entry)
{
	int		sep;

	sep = 21;
	while (sep < (int)ft_strlen(input_entry))
	{
		if (input_entry[sep - 1] != '\n')
			error_msg_exit("invalid separator: must be \\n");
		input_entry[sep - 1] = '@';
		sep += 21;
	}
}

void		check_input_length(int length)
{
	if (length == 0 || ((length + 1) % (MAX_TETRIMINO_SIZE + 1)) != 0)
		error_msg_exit("invalid file length");
}

void		check_tetri_chars(char *tetri_raw)
{
	int		i;

	i = 0;
	while (i < MAX_TETRIMINO_SIZE)
	{
		if ((((i + 1) % 5) == 0 && tetri_raw[i] != '\n')
			&& (tetri_raw[i] != CHAR_BLOCK && tetri_raw[i] != CHAR_EMPTY))
			error_msg_exit("invalid char");
		i++;
	}
}

void		parse_tetri(char *tetri_raw, t_tetrimino *t)
{
	char	**t_tab;
	char	*t_raw;
	int		i;

	if (!(t_tab = ft_strsplit(tetri_raw, '\n')))
		error_msg_exit("split 2 failed");
	if (!(t_raw = ft_strnew(16)))
		error_msg_exit(NULL);
	i = 0;
	while (t_tab[i])
	{
		ft_strcpy(t_raw + (i * 4), t_tab[i]);
		i++;
	}
	free_tab(&t_tab);
	t->value = raw_to_binary_represention(t_raw);
	if ((t->pattern_index = get_pattern(t->value)) == -1)
		error_msg_exit("invalid pattern");
	t->offset_x = 0;
	t->offset_y = 0;
	ft_strdel(&t_raw);
	set_v(t);
}

void		parse_entry(char *entry, t_map *map)
{
	char	**tetriminos_tab;
	char	**tmp_tab;
	int		tetri_index;

	if (!(tetriminos_tab = ft_strsplit(entry, '@')))
		error_msg_exit("split failed");
	tmp_tab = tetriminos_tab;
	tetri_index = 0;
	while (*tmp_tab)
	{
		check_tetri_chars(*tmp_tab);
		parse_tetri(*tmp_tab, &map->t[tetri_index]);
		tmp_tab++;
		tetri_index++;
	}
	free_tab(&tetriminos_tab);
	map->t_count = tetri_index;
}

void		parse(int fd, t_map *map)
{
	char	buffer[BUFFER_SIZE + 1];
	int		char_count;

	char_count = read_input(fd, buffer);
	check_input_length(char_count);
	prepare_entry_for_split(buffer);
	parse_entry(buffer, map);
}