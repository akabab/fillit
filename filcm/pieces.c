/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pieces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmutti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 15:36:03 by cmutti            #+#    #+#             */
/*   Updated: 2015/12/07 22:10:42 by ccouenon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		ft_adj(char *str, int i, int count)
{
	if (count == 4)
		return (1);
	if ((i - 3) % 5 != 0 && str[i + 1] == '#')
		return (1);
	if (i % 5 != 0 && i < 15 && str[i + 4] == '#' && str[i - 1] == '#')
		return (1);
	if ((i - 1) % 5 != 0 && i % 5 != 0 && i < 15 && str[i + 3] == '#')
		if (str[i - 1] == '#' && str[i - 2] == '#')
			return (1);
	if (i < 15 && str[i + 5] == '#')
		return (1);
	return (0);
}

static t_pieces	*ft_newpiece(void)
{
	t_pieces	*newelem;

	newelem = (t_pieces *)malloc(sizeof(*newelem));
	if (!newelem)
		return (NULL);
	newelem->pos = (int *)malloc(sizeof(int) * 6);
	if (!newelem->pos)
	{
		free(newelem);
		return (NULL);
	}
	newelem->pos[0] = -7;
	newelem->pos[1] = -7;
	newelem->pos[2] = -7;
	newelem->pos[3] = -7;
	newelem->pos[4] = -7;
	newelem->pos[5] = -7;
	newelem->next = NULL;
	return (newelem);
}

static void		ft_addpos(t_pieces *item, int pos, int first)
{
	if (item->pos[0] == -7)
	{
		item->pos[1] = pos / 5 - first / 5;
		item->pos[0] = pos % 5 - first % 5;
	}
	else if (item->pos[2] == -7)
	{
		item->pos[3] = pos / 5 - first / 5;
		item->pos[2] = pos % 5 - first % 5;
	}
	else if (item->pos[4] == -7)
	{
		item->pos[5] = pos / 5 - first / 5;
		item->pos[4] = pos % 5 - first % 5;
	}
}

static int		ft_addpieces(t_pieces **beginlist, char *s)
{
	t_pieces	*newitem;
	int			i;
	int			first;

	newitem = ft_newpiece();
	if (!newitem)
		return (0);
	i = -1;
	first = -1;
	while (s[++i])
	{
		if (s[i] == '#')
		{
			if (first == -1)
				first = i;
			else
				ft_addpos(newitem, i, first);
		}
	}
	ft_pushback(beginlist, newitem);
	return (1);
}

int				ft_check_addpieces(t_pieces **beginlist, char *s)
{
	int			i;
	int			x;
	int			size;

	i = -1;
	x = 0;
	size = 0;
	while (s[++i])
	{
		if (s[i] == '.' && ++x > 4)
			return (0);
		else if (s[i] == '\n')
		{
			if (x == 4 || (x == 0 && i != 0 && (s[i + 1] == '\0')))
				x = 0;
			else
				return (0);
		}
		else if (s[i] == '#' && (++size > 4 || ++x > 4 || !ft_adj(s, i, size)))
			return (0);
		else if (s[i] != '.' && s[i] != '#' && s[i] != '\n')
			return (0);
	}
	return (size != 4 ? 0 : ft_addpieces(beginlist, s));
}
