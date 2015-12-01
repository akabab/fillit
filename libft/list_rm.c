/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_rm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/19 17:30:03 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/23 17:24:46 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_destroy(t_list_node **begin)
{
	t_list_node	*cursor;
	t_list_node	*node_to_free;

	cursor = *begin;
	while (cursor)
	{
		node_to_free = cursor;
		cursor = cursor->next;
		free(node_to_free);
	}
}

void	list_clear(t_list_node **begin)
{
	t_list_node	*cursor;

	cursor = *begin;
	while (cursor)
	{
		free(cursor->value);
		cursor = cursor->next;
	}
}

void	list_clear_destroy(t_list_node **begin)
{
	list_clear(begin);
	list_destroy(begin);
}

void	list_remove_by_value(t_list_node **begin, void *value)
{
	t_list_node		*cursor;
	t_list_node		*del_node;

	del_node = NULL;
	if (value == (*begin)->value)
	{
		del_node = *begin;
		*begin = (*begin)->next;
	}
	else
	{
		cursor = *begin;
		while (cursor)
		{
			if (cursor->next->value == value)
			{
				del_node = cursor->next;
				cursor->next = cursor->next->next;
				break ;
			}
			cursor = cursor->next;
		}
	}
	free(del_node);
}

void	*list_remove(t_list_node **begin, t_list_node *node)
{
	void			*del_node_value;
	t_list_node		*cursor;

	del_node_value = NULL;
	if (node == *begin)
		*begin = (*begin)->next;
	else
	{
		cursor = *begin;
		while (cursor)
		{
			if (cursor->next == node)
			{
				cursor->next = node->next;
				break ;
			}
			cursor = cursor->next;
		}
	}
	del_node_value = node->value;
	free(node);
	return (del_node_value);
}
