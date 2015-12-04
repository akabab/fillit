t_bool		place(t_map *map, t_tetrimino *t)
{
	int			i;
	uint16_t	tmp_v[4];

	// test collision
	i = 0;
	while (i < 4) // [OPTI] -> test only for i < t->height
	{
		tmp_v[i] = t->v[i] >> offset_x;
		if (t->v[i] & map->m[t->offset_y])
			return (FALSE);
		i++;
	}
	// pas de collision -> insertion dans la map
	i = 0;
	while (i < 4)
	{
		map->m[t->offset_y] |= tmp_v[i];
		i++;
	}
	return (TRUE);
}

t_bool		solve(t_map *map, int tetri_index)
{
	t_tetrimino		*t;

	if (tetri_index > map->t_count) // all placés
		return (1);
	t = map->t[tetri_index];
	while (t->offset_y < map->size) // pas en buté avec la map en bas
	{
		while (t->offset_x < map->size) // pas en buté avec la map a droite
		{
			if (place(map, map->t[tetri_index]))
			{
				if (solve(map, tetri_index + 1))
					return (1);
			}
			t->offset_x++;
		}
		t->offset_y++;
	}
	return (0);
}