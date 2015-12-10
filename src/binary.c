#include "fillit.h"

static uint16_t		move_to_most_top_left_position(uint16_t value)
{
	while ((value & LEFT_MASK) == 0)
		value <<= 1;
	while ((value & TOP_MASK) == 0)
		value <<= 4;
	return (value);
}

uint16_t			raw_to_binary_represention(char *raw)
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
