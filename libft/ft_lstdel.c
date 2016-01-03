/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 16:14:19 by ycribier          #+#    #+#             */
/*   Updated: 2014/01/21 16:46:43 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*to_free;

	if (alst)
	{
		while (*alst)
		{
			del((*alst)->content, (*alst)->content_size);
			to_free = *alst;
			*alst = (*alst)->next;
			free(to_free);
			to_free = NULL;
		}
	}
}
