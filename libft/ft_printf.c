/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:30:41 by sparth            #+#    #+#             */
/*   Updated: 2023/11/07 18:03:27 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putcharprint(char c)
{
	return (write(2, &c, 1));
}

int	ft_putstrprint(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		i += write(2, "(null)", 6);
		return (i);
	}
	while (*str)
		i += ft_putcharprint(*(str++));
	return (i);
}

int	pnbr(unsigned long n, char *base, unsigned int baselen, int uns)
{
	int	count;

	count = 0;
	if (uns == -1 && n > INT_MAX)
	{
		count += ft_putcharprint('-');
		n = (UINT_MAX - n) + 1;
	}
	if (uns == 1)
	{
		count += write(2, "0x", 2);
		uns++;
	}
	if (n >= baselen)
	{
		count += pnbr(n / baselen, base, baselen, uns);
		count += ft_putcharprint(base[n % baselen]);
	}
	if (n < baselen)
		count += ft_putcharprint(base[n]);
	return (count);
}

int	printtype(const char *instructions, va_list *ap)
{
	if (*instructions == 'c')
		return (ft_putcharprint(va_arg(*ap, int)));
	if (*instructions == 's')
		return (ft_putstrprint(va_arg(*ap, char *)));
	if (*instructions == 'p')
		return (pnbr((va_arg(*ap, unsigned long)), "0123456789abcdef", 16, 1));
	if (*instructions == 'd' || *instructions == 'i')
		return (pnbr((va_arg(*ap, unsigned int)), "0123456789", 10, -1));
	if (*instructions == 'u')
		return (pnbr((va_arg(*ap, unsigned int)), "0123456789", 10, 0));
	if (*instructions == 'x')
		return (pnbr((va_arg(*ap, unsigned int)), "0123456789abcdef", 16, 0));
	if (*instructions == 'X')
		return (pnbr((va_arg(*ap, unsigned int)), "0123456789ABCDEF", 16, 0));
	if (*instructions == '%')
		return (ft_putcharprint('%'));
	return (-1);
}

int	ft_printf(const char *instructions, ...)
{
	int		count;
	va_list	ap;

	count = 0;
	va_start(ap, instructions);
	while (*instructions)
	{
		if (*instructions != '%')
			count += ft_putcharprint(*instructions);
		if (*instructions == '%')
			count += printtype(++instructions, &ap);
		instructions++;
	}
	va_end(ap);
	return (count);
}
