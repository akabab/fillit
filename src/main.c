#include "libft.h"
#include "fillit.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h> //

// [OPTI] -> by ref instead of copy ( is struct copied ? )
t_bool	collide(t_tetrimino tetri_a, uint64_t *buffer, uint64_t *hbuffer)
{
	uint64_t 		ret;
	uint64_t 		hret;
	uint64_t		tmp_b_value;
	uint64_t		tmp_a_value;
	uint64_t		temp;
	uint64_t		htemp;

	temp = *buffer;
	htemp = *hbuffer;
	tmp_b_value = tetri_a.value;
	tmp_a_value = tetri_a.hvalue;

	ft_putendl("start");
	print_tetriminos(tetri_a.value);
	//	print_tetriminos(tetri_a.hvalue);
	print_tetriminos_long(*buffer);
	print_tetriminos_long(tmp_b_value);
	print_tetriminos_long(temp |= tmp_b_value);
	htemp |= tmp_a_value;
	ret = (temp ^ tmp_b_value);
	hret = (htemp ^ tmp_a_value);
	ft_putendl("temp");
	print_tetriminos(temp);
	//	print_tetriminos(htemp);
	ft_putendl("rets");
	print_tetriminos_long(ret);
	//	print_tetriminos_long(hret);
	if (ret == *buffer)
	{
		*buffer = temp;
		*hbuffer = htemp;
		ft_putendl("result");
		print_tetriminos(*buffer);
		//		print_tetriminos(*hbuffer);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	vertical_collide(t_tetrimino tetri_a, uint64_t *h_buffer, uint64_t *v_buffer)
{
	uint64_t 		ret;
	uint64_t		tmp_a_value;
	uint64_t		temp;

	temp = *v_buffer;
	if (tetri_a.index == 1)
	{
		tetri_a.offset_y = -1;
		ft_putnbr(tetri_a.offset_x);
	}
	tmp_a_value = move(tetri_a.hvalue, tetri_a.offset_y);
	temp |= tmp_a_value;
	ret = (temp ^ tmp_a_value);
	ft_putendl("vertical_try");
	print_tetriminos(*v_buffer);
	print_tetriminos(tmp_a_value);
	if (ret == *v_buffer)
	{
		*v_buffer = temp;
		return(TRUE);	
	}
	tetri_a.offset_y = 0;
	return (FALSE);
}

t_bool	horizontal_collide(t_tetrimino tetri_a, uint64_t *h_buffer, uint64_t *v_buffer)
{
	uint64_t 		ret;
	uint64_t		tmp_a_value;
	uint64_t		temp;

	while (tetri_a.offset_x > -16)
	{
		temp = *h_buffer;
		tmp_a_value = move(tetri_a.value, tetri_a.offset_x);
		temp |= tmp_a_value;
		ret = (temp ^ tmp_a_value);
		tetri_a.offset_x -= 2;
		if (ret == *h_buffer)
		{
			*h_buffer = temp;
			if (vertical_collide(tetri_a, h_buffer, v_buffer))
			return(TRUE);
		}
	}
	tetri_a.offset_x = 0;
	return (FALSE);
}

void	test_bit_shifting()
{
	uint16_t	t = 1 << 1;
	print_16bit_representation_of_int(t);
	t >>= 2;
	print_16bit_representation_of_int(t);
	t <<= 2;
	print_16bit_representation_of_int(t);
}

#define NOT 1;


//backtracking, trouve une solution
int	place_them(t_tetrimino *tetriminos, t_result answer)
{
	uint64_t			h_buffer;
	uint64_t			v_buffer;
	int				index;

	index = 0;
	v_buffer = answer.v_buffer;
	h_buffer = answer.h_buffer;
	while (index < answer.count)
	{	
		if (!tetriminos[index].used)
		{
			if (horizontal_collide(tetriminos[index], &h_buffer, &v_buffer))
			{
				tetriminos[index].used = 1;
				print_tetriminos(h_buffer);
				answer.h_buffer = h_buffer;
				answer.v_buffer = v_buffer;
				if (place_them(tetriminos, answer) == 1)
					return (1);
			}
		}
		index++;
	}
	return (1);
}

int		main(int ac, char *av[])
{
	int				fd;
	t_tetrimino			tetriminos[MAX_TETRIMINOS];
	int				tetriminos_count;
	uint64_t			buffer;
	uint64_t			hbuffer;
	t_result			answer;

	// test_bit_shifting();
	buffer = 0;
	hbuffer = 0;
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
	// PARSE
	tetriminos_count = parse(fd, tetriminos);
	answer.count = tetriminos_count;
	answer.limit = -8; 
	answer.v_buffer = 0;
	answer.h_buffer = 0;
	// VERIF
	// int i = 0;
	// while (i < tetriminos_count)
	// {
	// 	printf("%s -> %d\n", tetriminos[i].raw, tetriminos[i].value);
	// 	i++;
	// }

	// RESOLVE
	// ...
	place_them(tetriminos, answer);
}
