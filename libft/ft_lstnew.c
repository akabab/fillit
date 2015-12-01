/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 14:29:02 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/28 18:52:04 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!(new->content = ft_memalloc(content_size)))
	{
		free(new);
		return (NULL);
	}
	if (content)
		ft_memcpy(new->content, content, content_size);
	new->content_size = content ? content_size : 0;
	new->next = NULL;
	return (new);
}
