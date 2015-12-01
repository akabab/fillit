/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 21:25:41 by mguinin           #+#    #+#             */
/*   Updated: 2014/03/14 14:33:15 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"

int			print_int(int a)
{
	int		len;

	ft_putnbr(a);
	len = 1 + (a < 0);
	while ((a /= 10))
		len++;
	return (len);
}

int			print_str(char *str)
{
	str = str ? str : "(null)";
	ft_putstr(str);
	return (ft_strlen(str));
}

int			print_addr(intptr_t addr, int ox)
{
	static char		hexa[] = "0123456789abcdef";
	int				len;

	if (ox)
		write(1, "0x", 2);
	if (addr || ox)
	{
		len = 1 + print_addr(addr >> 4, 0) + 2 * ox;
		ft_putchar(hexa[addr & 15]);
		return (len);
	}
	return (0);
}

static int	print_arg(const char **format, va_list *arg)
{
	char		c;

	(*format)++;
	c = *((*format)++);
	if (c == 'd')
		return (print_int(va_arg(*arg, int)));
	else if (c == 's')
		return (print_str(va_arg(*arg, char*)));
	else if (c == 'c')
	{
		ft_putchar(va_arg(*arg, int));
		return (1);
	}
	else if (c == 'p')
		return (print_addr(va_arg(*arg, intptr_t), 1));
	ft_putchar(c);
	return (1);
}

int			ft_printf(const char *format, ...)
{
	va_list		arg;
	int			i;
	int			len;

	if (!format)
		return (0);
	va_start(arg, format);
	len = 0;
	while (*format)
	{
		i = 0;
		while (format[i] && format[i] != '%')
			i++;
		if (i)
			write(1, format, i);
		format += i;
		len += i;
		if (*format)
			len += print_arg(&format, &arg);
	}
	va_end(arg);
	return (len);
}
