/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_oct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 16:41:56 by ycribier          #+#    #+#             */
/*   Updated: 2014/03/12 17:01:46 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		decimal_to_octal(int n)
{
	int		octal;
	int		rest;
	int		i;

	octal = 0;
	i = 1;
	while (n != 0)
	{
		rest = n % 8;
		n /= 8;
		octal += rest * i;
		i *= 10;
	}
	return (octal);
}

int		octal_to_decimal(int n)
{
	int		decimal;
	int		rest;
	int		i;

	decimal = 0;
	i = 0;
	while (n != 0)
	{
		rest = n % 10;
		n /= 10;
		decimal += rest * ft_power(8, i);
		i++;
	}
	return (decimal);
}
