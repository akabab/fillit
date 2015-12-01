/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 12:44:13 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/28 19:22:53 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static char		*safe_join(char *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	s1_len = (s1) ? ft_strlen(s1) : 0;
	s2_len = ft_strlen(s2);
	result = ft_strnew(s1_len + s2_len);
	if (result)
	{
		if (s1)
			ft_memcpy(result, s1, s1_len);
		ft_memcpy(result + s1_len, s2, s2_len);
	}
	if (s1)
		ft_strdel(&s1);
	return (result);
}

static int		cut_at_newline(char **s_buff, char **line)
{
	char	*at;

	if ((at = ft_strchr(*s_buff, '\n')))
	{
		*line = ft_strsub(*s_buff, 0, at - *s_buff);
		ft_strcpy(*s_buff, at + 1);
		return (1);
	}
	return (0);
}

static void		clear(char **s_buff, char **line)
{
	if (*s_buff)
		ft_strdel(s_buff);
	ft_strdel(line);
}

int				get_next_line(int const fd, char **line)
{
	int				bytes_read;
	char			buff[BUFF_SIZE + 1];
	static char		*s_buff = NULL;

	if (!line)
		return (-1);
	if (s_buff && cut_at_newline(&s_buff, line))
		return (1);
	while ((bytes_read = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[bytes_read] = '\0';
		s_buff = safe_join(s_buff, buff);
		if (cut_at_newline(&s_buff, line))
			return (1);
	}
	if (bytes_read == -1)
		return (-1);
	if (s_buff && *s_buff)
	{
		*line = ft_strdup(s_buff);
		ft_strdel(&s_buff);
		return (1);
	}
	clear(&s_buff, line);
	return (0);
}
