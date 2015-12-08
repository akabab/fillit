/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmutti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 13:27:45 by cmutti            #+#    #+#             */
/*   Updated: 2015/12/07 22:12:21 by ccouenon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		ft_pushback(t_pieces **begin_list, t_pieces *newelem)
{
	t_pieces	*tmp;
	int			i;

	i = 1;
	if (begin_list && *begin_list)
	{
		tmp = *begin_list;
		while (tmp->next)
		{
			i++;
			tmp = tmp->next;
		}
		tmp->next = newelem;
		newelem->letter = 'A' + i;
	}
	else
	{
		*begin_list = newelem;
		newelem->letter = 'A';
	}
}

t_pieces	*ft_freelst(t_pieces **begin_list)
{
	t_pieces	*tmp;
	t_pieces	*next;
	int			i;

	i = 0;
	if (begin_list && *begin_list)
	{
		tmp = *begin_list;
		while (tmp)
		{
			i++;
			next = tmp->next;
			tmp->next = NULL;
			free(tmp->pos);
			free(tmp);
			tmp = next;
		}
		*begin_list = NULL;
	}
	return (NULL);
}

char		*ft_inittab(char *tab, int size)
{
	int		i;

	tab = ft_strnew((size + 1) * (size + 1));
	if (!tab)
		return (NULL);
	i = -1;
	while (++i <= size * (size + 1))
	{
		if (i % (size + 1) == 0)
			tab[i] = '\n';
		else
			tab[i] = '.';
	}
	return (tab);
}

int			ft_putstrerr(char *s, int ret)
{
	ft_putstr(s);
	return (ret);
}
