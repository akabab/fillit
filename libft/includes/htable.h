/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htable.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 10:54:37 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/28 18:05:38 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTABLE_H
# define HTABLE_H

# include <stdlib.h>
# include "libft.h"
# include "list.h"

typedef struct		s_htable
{
	int				size;
	unsigned int	(*hash_ft)(struct s_htable *, char *);
	t_list_node		**table;
}					t_htable;

t_htable			*htable_create(int size);
int					htable_add(t_htable *htable, char *str);
t_list_node			*htable_get(t_htable *htable, char *str);
int					htable_count(t_htable *htable);

void				htable_destroy(t_htable *htable);
void				htable_clear(t_htable *htable);
void				htable_clear_destroy(t_htable *htable);
void				*htable_remove(t_htable *htable, char *str);

/*
**		Hash functions
*/

unsigned int		hash_djb2(t_htable *htable, char *str);
unsigned int		hash_sum(t_htable *htable, char *str);

#endif
