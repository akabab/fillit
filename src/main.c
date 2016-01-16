#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "fillit.h"


void		clear(t_map *map)
{
	int		i;

	i = 0;
	map->grid = 0;
	map->grid_plus = 0;
	ft_bzero(map->dyn_pos, sizeof(map->dyn_pos));
	map->resolve = (map->size < 12) ? resolve : resolve_plus;
	while (i < map->t_count)
	{
		map->t[i].offset.x = 0;
		map->t[i].offset.y = 0;
		map->t[i].new_value = move_to_most_top_left64_position(map->t[i].value);
		map->t[i].new_value = new_form(map->t[i].new_value, map->size);
		map->t[i].max_offset = map->total_space - (map->t[i].height * map->size);
		map->t[i].max_grid = 128 - (map->t[i].height * map->size);
		map->t[i].limit_line = map->size - map->t[i].width;
		i++;
	}
}

void		solve(t_map *map)
{
	map->space_required = map->t_count * 4;
	map->size = ft_ceil_sqrt(map->space_required);
	while (map->size < 16)
	{
		map->total_space = map->size * map->size;
		clear(map);
		if (map->resolve(map, 0, map->size))
		{
			print_result_map(map);
			break ;
		}
		map->size++;
	}
}

int			main(int ac, char *av[])
{
	int		fd;
	t_map	map;

	if (ac != 2)
	{
		fillit_error_msg_exit("Usage: ./fillit [map.fillit]");
		return (-1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		fillit_error_msg_exit("some open failed somewhere");
	ft_memset(&map, 0, sizeof(map));
	parse(fd, &map);
	close(fd);
	solve(&map);
	return (0);
}
