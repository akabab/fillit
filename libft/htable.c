/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htable.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 10:54:06 by ycribier          #+#    #+#             */
/*   Updated: 2014/02/21 22:58:55 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

t_htable		*htable_create(int size)
{
	t_htable	*htable;
	int			i;

	if (size < 1)
		return (NULL);
	if ((htable = malloc(sizeof(t_htable))) == NULL)
		return (NULL);
	if ((htable->table = malloc(sizeof(t_list_node *) * size)) == NULL)
	{
		free(htable);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		htable->table[i] = NULL;
		i++;
	}
	htable->size = size;
	htable->hash_ft = &hash_sum;
	return (htable);
}

int				htable_add(t_htable *htable, char *str)
{
	unsigned int	hashval;

	hashval = htable->hash_ft(htable, str);
	list_push_front(&(htable->table[hashval]), str);
	return (0);
}

t_list_node		*htable_get(t_htable *htable, char *str)
{
	t_list_node		*cursor;
	unsigned int	hashval;

	hashval = htable->hash_ft(htable, str);
	cursor = htable->table[hashval];
	while (cursor)
	{
		if (ft_strequ((char *)(cursor->value), str))
			return (cursor);
		cursor = cursor->next;
	}
	return (NULL);
}

int				htable_count(t_htable *htable)
{
	int				i;
	int				count;
	t_list_node		*cursor;

	count = 0;
	if (!htable)
		return (-1);
	i = 0;
	while (i < htable->size)
	{
		cursor = htable->table[i];
		while (cursor)
		{
			count++;
			cursor = cursor->next;
		}
		i++;
	}
	return (count);
}
