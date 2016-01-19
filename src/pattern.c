#include "fillit.h"
/*
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
*/
void			fill_structure(t_pattern *g_pattern, int value,
		int gap_x, int width, int height)
{
	g_pattern->value = value;
	g_pattern->gap_x = gap_x;
	g_pattern->width = width;
	g_pattern->height = height;
}

void			fill_patterns(t_pattern *g_patterns)
{
	int			i;

	i = 0;
	fill_structure(&g_patterns[i++],  57856, 3, 3, 2 );
	fill_structure(&g_patterns[i++],  17600, 2, 2, 3 );
	fill_structure(&g_patterns[i++],  36352, 3, 3, 2 );
	fill_structure(&g_patterns[i++],  51328, 2, 2, 3 );
	fill_structure(&g_patterns[i++],  59392, 3, 3, 2 );
	fill_structure(&g_patterns[i++],  50240, 2, 2, 3 );
	fill_structure(&g_patterns[i++],  11776, 3, 3, 2 );
	fill_structure(&g_patterns[i++],  35008, 2, 2, 3 );
	fill_structure(&g_patterns[i++],  58368, 3, 3, 2 );
	fill_structure(&g_patterns[i++],  19520, 2, 2, 3 );
	fill_structure(&g_patterns[i++],  19968, 3, 3, 2 );
	fill_structure(&g_patterns[i++],  35968, 2, 2, 3 );
	fill_structure(&g_patterns[i++],  27648, 2, 3, 2 );
	fill_structure(&g_patterns[i++],  35904, 2, 2, 3 );
	fill_structure(&g_patterns[i++],  50688, 2, 3, 2 );
	fill_structure(&g_patterns[i++],  19584, 2, 2, 3 );
	fill_structure(&g_patterns[i++],  61440, 4, 4, 1 );
	fill_structure(&g_patterns[i++],  34952, 1, 1, 4 );
	fill_structure(&g_patterns[i++],  52224, 2, 2, 2 );
}

int				get_matched_pattern_index(t_tetrimino *t)
{
	int			i;
	int			value;
	t_pattern	*g_patterns;

	i = 0;
	value = t->value;
	g_patterns = malloc(sizeof(t_pattern) * 19);
	if (!g_patterns)
		return (-1);
	fill_patterns(g_patterns);
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
