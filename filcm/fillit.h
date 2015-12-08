/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmutti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 14:56:08 by cmutti            #+#    #+#             */
/*   Updated: 2015/12/07 22:12:57 by ccouenon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FILLIT_H
# define _FILLIT_H

# include "libft.h"
# include <stdlib.h>

typedef struct		s_pieces
{
	int				*pos;
	struct s_pieces	*next;
	char			letter;
}					t_pieces;

int					ft_putstrerr(char *str, int ret);
int					ft_check_addpieces(t_pieces **beginlist, char	*str);
int					ft_filltab2(t_pieces *piece, char *tab, int size, int i);
char				*ft_inittab(char *tab, int size);
void				ft_pushback(t_pieces **begin_list, t_pieces *newelem);
t_pieces			*ft_freelst(t_pieces **begin_list);

#endif
