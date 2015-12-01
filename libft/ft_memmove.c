/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 10:54:03 by ycribier          #+#    #+#             */
/*   Updated: 2013/11/22 10:54:12 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memmove(void *dst, void const *src, size_t n)
{
	size_t		i;
	char		*tmp_d;
	char		*tmp_s;
	const char	*tmp;

	i = 0;
	tmp_d = dst;
	tmp = src;
	tmp_s = malloc(sizeof(char) * n);
	while (i < n)
	{
		tmp_s[i] = tmp[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		tmp_d[i] = tmp_s[i];
		i++;
	}
	free(tmp_s);
	return (dst);
}
