/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/19 16:25:54 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/13 14:02:57 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/*
**		Returns the node pushed
*/

t_list_node		*list_push_back(t_list_node **begin, void *value)
{
	t_list_node		*node;
	t_list_node		*cursor;

	node = malloc(sizeof(t_list_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	if (!*begin)
		*begin = node;
	else
	{
		cursor = *begin;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = node;
	}
	return (node);
}

void			*list_pop_back(t_list_node **begin)
{
	t_list_node		*node;

	if (!*begin)
		return (NULL);
	node = *begin;
	while (node->next)
		node = node->next;
	return (list_remove(begin, node));
}

void			list_push_front(t_list_node **begin, void *value)
{
	t_list_node		*node;

	node = malloc(sizeof(t_list_node));
	if (!node)
		return ;
	node->value = value;
	if (!*begin)
		node->next = NULL;
	else
		node->next = *begin;
	*begin = node;
}

void			*list_pop_front(t_list_node **begin)
{
	t_list_node		*node;

	if (!*begin)
		return (NULL);
	node = *begin;
	return (list_remove(begin, node));
}
