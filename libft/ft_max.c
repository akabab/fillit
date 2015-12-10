/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 11:27:47 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/01 11:29:22 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

float		ft_fmax(float x, float y)
{
	if (x > y)
		return (x);
	return (y);
}

double		ft_dmax(double x, double y)
{
	if (x > y)
		return (x);
	return (y);
}
