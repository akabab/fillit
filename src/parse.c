/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 10:42:11 by ycribier          #+#    #+#             */
/*   Updated: 2015/12/11 10:47:50 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "fillit.h"

static void		prepare_entry_for_split(char *input_entry)
{
	int			sep;

	sep = 21;
	while (sep < (int)ft_strlen(input_entry))
	{
		if (input_entry[sep - 1] != '\n')
			fillit_error_msg_exit("invalid separator: must be \\n");
		input_entry[sep - 1] = '@';
		sep += 21;
	}
}

static void		check_input_length(int length)
{
	if (length == 0 || ((length + 1) % (MAX_TETRIMINO_SIZE + 1)) != 0)
		fillit_error_msg_exit("invalid file length");
}

static int		read_input(int fd, char *buffer)
{
	int			char_count;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	char_count = read(fd, buffer, BUFFER_SIZE);
	if (char_count == -1)
		fillit_error_msg_exit("some read failed somewhere");
	return (char_count);
}

void			parse(int fd, t_map *map)
{
	char		buffer[BUFFER_SIZE + 1];
	int			char_count;

	char_count = read_input(fd, buffer);
	check_input_length(char_count);
	prepare_entry_for_split(buffer);
	parse_entry(buffer, map);
}
