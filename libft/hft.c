/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hft.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 11:10:44 by ycribier          #+#    #+#             */
/*   Updated: 2014/02/21 22:59:07 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

/*
**	djb2
**	This algorithm was first reported by Dan Bernstein
**	many years ago in comp.lang.c
**	other implementation --> / hash = ((hash << 5) + hash) * 33 + c; /
*/

unsigned int	hash_djb2(t_htable *htable, char *str)
{
	unsigned int	hash;
	int				c;

	hash = 5381;
	while (str && *str)
	{
		c = *str;
		hash = ((hash << 5) + hash) + c;
		str++;
	}
	return (hash % htable->size);
}

unsigned int	hash_sum(t_htable *htable, char *str)
{
	unsigned int	hash;

	hash = 0;
	while (str && *str)
	{
		hash = *str + (hash << 5) - hash;
		str++;
	}
	return (hash % htable->size);
}
