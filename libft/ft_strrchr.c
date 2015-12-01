/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 11:04:19 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/28 17:59:53 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(char const *str, int c)
{
	size_t	i;
	char	*occ;

	i = 0;
	occ = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			occ = (char *)&str[i];
		i++;
	}
	if (str[i] == c)
		occ = (char *)&str[i];
	if (occ != NULL)
		return (occ);
	else
		return (0);
}
