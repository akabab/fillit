/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degree_radian.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 18:58:47 by ycribier          #+#    #+#             */
/*   Updated: 2014/01/13 18:59:01 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	fdeg(double value)
{
	value = fmod(value, 360);
	if (value < 0)
		value += 360;
	return (value);
}

double	frad(double value)
{
	value = fmod(value, 2 * M_PI);
	if (value < 0)
		value += 2 * M_PI;
	return (value);
}

double	frad_to_deg(double value)
{
	value = fdeg(value) / M_PI * 180;
	return (value);
}

double	fdeg_to_rad(double value)
{
	value = fdeg(value) * M_PI / 180;
	return (value);
}
