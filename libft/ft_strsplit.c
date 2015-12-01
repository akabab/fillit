/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 18:53:26 by ycribier          #+#    #+#             */
/*   Updated: 2015/04/07 17:37:23 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

size_t	ft_wordsize(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (*s != '\0' && *s != c)
	{
		s++;
		size++;
	}
	return (size);
}

size_t	ft_countwords(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**ptr;
	size_t	nb_words;
	size_t	i;
	size_t	word_size;

	nb_words = ft_countwords(s, c);
	ptr = malloc((nb_words + 1) * sizeof(*ptr));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < nb_words && *s != '\0')
	{
		while (*s == c)
			s++;
		word_size = ft_wordsize(s, c);
		ptr[i] = malloc((word_size + 1) * sizeof(**ptr));
		if (ptr[i] == NULL)
			return (NULL);
		ft_strncpy(ptr[i], s, word_size);
		ptr[i][word_size] = '\0';
		s += word_size;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_strsplit_once(char const *s, char c)
{
	char	*at;
	size_t	at_index;
	char	**tab;

	tab = NULL;
	if ((at = ft_strchr(s, c)))
	{
		if (!(tab = ft_memalloc(sizeof(char *) * (2 + 1))))
			return (NULL);
		at_index = at - s;
		tab[0] = ft_strsub(s, 0, at_index);
		tab[1] = ft_strsub(s, at_index + 1, ft_strlen(s) - (at_index + 1));
		tab[2] = NULL;
	}
	return (tab);
}
