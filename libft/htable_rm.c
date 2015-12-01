/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htable_rm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 16:14:13 by ycribier          #+#    #+#             */
/*   Updated: 2014/02/21 22:59:00 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

void		htable_destroy(t_htable *htable)
{
	int				i;
	t_list_node		*cursor;
	t_list_node		*node_to_free;

	if (!htable)
		return ;
	i = 0;
	while (i < htable->size)
	{
		cursor = htable->table[i];
		while (cursor)
		{
			node_to_free = cursor;
			cursor = cursor->next;
			free(node_to_free);
		}
		i++;
	}
	free(htable->table);
	free(htable);
}

void		htable_clear(t_htable *htable)
{
	int				i;
	t_list_node		*cursor;

	if (!htable)
		return ;
	i = 0;
	while (i < htable->size)
	{
		cursor = htable->table[i];
		while (cursor)
		{
			free(cursor->value);
			cursor = cursor->next;
		}
		i++;
	}
}

void		htable_clear_destroy(t_htable *htable)
{
	htable_clear(htable);
	htable_destroy(htable);
}

void		*htable_remove(t_htable *htable, char *str)
{
	t_list_node		*cursor;
	t_list_node		*prev;
	void			*del_node_value;
	unsigned int	hashval;

	hashval = htable->hash_ft(htable, str);
	cursor = htable->table[hashval];
	prev = NULL;
	while (cursor && ft_strequ((char *)(cursor->value), str) == 0)
	{
		prev = cursor;
		cursor = cursor->next;
	}
	if (!cursor)
		return (NULL);
	if (!prev)
		htable->table[hashval] = cursor->next;
	else
		prev->next = cursor->next;
	del_node_value = cursor->value;
	free(cursor);
	return (del_node_value);
}
