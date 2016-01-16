#include "fillit.h"

static const t_pattern		g_patterns[TETRI_PATTERNS_COUNT] = {
	{ 57856, 3, 3, 2 },
	{ 17600, 2, 2, 3 },
	{ 36352, 3, 3, 2 },
	{ 51328, 2, 2, 3 },
	{ 59392, 3, 3, 2 },
	{ 50240, 2, 2, 3 },
	{ 11776, 3, 3, 2 },
	{ 35008, 2, 2, 3 },
	{ 58368, 3, 3, 2 },
	{ 19520, 2, 2, 3 },
	{ 19968, 3, 3, 2 },
	{ 35968, 2, 2, 3 },
	{ 27648, 2, 3, 2 },
	{ 35904, 2, 2, 3 },
	{ 50688, 2, 3, 2 },
	{ 19584, 2, 2, 3 },
	{ 61440, 4, 4, 1 },
	{ 34952, 1, 1, 4 },
	{ 52224, 2, 2, 2 }
};

int			get_matched_pattern_index(t_tetrimino *t)
{
	int		i;
	int		value;

	i = 0;
	value = t->value;
	while (i < TETRI_PATTERNS_COUNT)
	{
		if (value == g_patterns[i].value)
		{
			t->height = g_patterns[i].height;
			t->width = g_patterns[i].width;
			t->gap_x = g_patterns[i].gap_x;
			return (i);
		}
		i++;
	}
	return (-1);
}
