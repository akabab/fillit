/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmutti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 14:55:49 by cmutti            #+#    #+#             */
/*   Updated: 2015/12/07 22:14:20 by ccouenon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <fcntl.h>
#include "libft.h"
#include <unistd.h>

static t_pieces		*ft_getpieces(int fd)
{
	char		buff[22];
	t_pieces	*beginlst;
	int			ret;
	int			j;

	beginlst = NULL;
	j = 0;
	while ((ret = read(fd, buff, 20)))
	{
		if (ret < 20)
			return (ft_freelst(&beginlst));
		buff[ret] = '\0';
		if (!ft_check_addpieces(&beginlst, buff))
			return (ft_freelst(&beginlst));
		if (++j > 26)
			return (ft_freelst(&beginlst));
		if (!(read(fd, buff, 1)))
			break ;
		if (buff[0] != '\n' && buff[0] != '\0')
			return (ft_freelst(&beginlst));
	}
	if (buff[0] == '\n')
		return (ft_freelst(&beginlst));
	return (beginlst);
}

static int			ft_filltab(t_pieces *piece, char *tab, int size, int i)
{
	if (!piece)
		return (1);
	while (tab[i] != '.' && tab[i])
		i++;
	if (tab[i] == '\0' || tab[i + 1] == '\0' || tab[i + 2] == '\0'
		|| tab[i + 3] == '\0')
		return (0);
	tab[i] = piece->letter;
	if (tab[i + piece->pos[0] + piece->pos[1] * (size + 1)] == '.')
		tab[i + piece->pos[0] + piece->pos[1] * (size + 1)] = piece->letter;
	else
	{
		tab[i] = '.';
		return (ft_filltab(piece, tab, size, i + 1));
	}
	return (ft_filltab2(piece, tab, size, i));
}

int					ft_filltab2(t_pieces *piece, char *tab, int size, int i)
{
	if (tab[i + piece->pos[2] + piece->pos[3] * (size + 1)] == '.')
		tab[i + piece->pos[2] + piece->pos[3] * (size + 1)] = piece->letter;
	else
	{
		tab[i] = '.';
		tab[i + piece->pos[0] + piece->pos[1] * (size + 1)] = '.';
		return (ft_filltab(piece, tab, size, i + 1));
	}
	if (tab[i + piece->pos[4] + piece->pos[5] * (size + 1)] == '.')
		tab[i + piece->pos[4] + piece->pos[5] * (size + 1)] = piece->letter;
	else
	{
		tab[i] = '.';
		tab[i + piece->pos[0] + piece->pos[1] * (size + 1)] = '.';
		tab[i + piece->pos[2] + piece->pos[3] * (size + 1)] = '.';
		return (ft_filltab(piece, tab, size, i + 1));
	}
	if (ft_filltab(piece->next, tab, size, 0))
		return (1);
	tab[i] = '.';
	tab[i + piece->pos[0] + piece->pos[1] * (size + 1)] = '.';
	tab[i + piece->pos[2] + piece->pos[3] * (size + 1)] = '.';
	tab[i + piece->pos[4] + piece->pos[5] * (size + 1)] = '.';
	return (ft_filltab(piece, tab, size, i + 1));
}

static char			*ft_gettab(t_pieces **lststart)
{
	int			i;
	int			size;
	char		*tab;
	t_pieces	*tmp;

	i = 0;
	size = 2;
	tmp = *lststart;
	tab = NULL;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	while (size * size < i * 4)
		++size;
	if (!(tab = ft_inittab(tab, size)))
		return (NULL);
	while (!ft_filltab(*lststart, tab, size, 0))
	{
		ft_strdel(&tab);
		if (!(tab = ft_inittab(tab, ++size)))
			return (NULL);
	}
	return (tab);
}

int					main(int argc, char **argv)
{
	int			fd;
	char		*tab;
	t_pieces	*lststart;

	if (argc != 2)
		return (ft_putstrerr("error\n", 0));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstrerr("error\n", 0));
	lststart = ft_getpieces(fd);
	if (!lststart)
		return (ft_putstrerr("error\n", 0));
	tab = ft_gettab(&lststart);
	if (!tab)
		return (ft_freelst(&lststart) || ft_putstrerr("error\n", 0));
	ft_putstr(tab + 1);
	ft_strdel(&tab);
	close(fd);
	ft_freelst(&lststart);
	return (0);
}
