/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 20:11:01 by ycribier          #+#    #+#             */
/*   Updated: 2014/02/05 19:31:30 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **begin, t_list *new)
{
	t_list		*cur;

	if (!begin || !new)
		return ;
	if (!*begin)
	{
		*begin = new;
		return ;
	}
	cur = *begin;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}
