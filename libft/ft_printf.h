/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:25:42 by sparth            #+#    #+#             */
/*   Updated: 2023/11/03 15:27:38 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

int	ft_printf(const char *instructions, ...);
int	printtype(const char *instructions, va_list *ap);
int	pnbr(unsigned long n, char *base, unsigned int baselen, int uns);
int	ft_putstrprint(char *str);
int	ft_putcharprint(char c);

#endif