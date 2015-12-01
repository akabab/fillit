/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 01:47:21 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/08 23:47:27 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_tab(char ***tab)
{
	char	**tmp;

	tmp = *tab;
	while (**tab)
	{
		free(**tab);
		(*tab)++;
	}
	free(tmp);
}

void	free_ntab(char ***tab, int n)
{
	char	**tmp;

	tmp = *tab;
	while (n)
	{
		free(**tab);
		(*tab)++;
		n--;
	}
	free(tmp);
}
