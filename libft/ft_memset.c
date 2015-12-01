/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 10:53:05 by ycribier          #+#    #+#             */
/*   Updated: 2014/02/05 16:27:28 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *mem, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)mem)[i] = (unsigned char)c;
		i++;
	}
	return (mem);
}
