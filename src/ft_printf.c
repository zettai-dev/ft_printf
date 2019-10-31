/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouahib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:46:44 by aouahib           #+#    #+#             */
/*   Updated: 2019/10/31 14:20:14 by aouahib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>
static int	put_printf(t_printf *pf, va_list *vl, int res)
{
	char	c;

	c = pf->type;
	if (!pf_istype(c))
	{
		ft_putchar(c);
		return (1);
	}
	if (c == 's')
		return (pf_putstr(pf, vl));
	else if (c == 'c' || c == 'd' || c == 'i' || c == 'u')
		return (pf_putint(pf, vl));
	else if (c == 'p' || c == 'x' || c == 'X')
		return (pf_puthex(pf, vl));
	else if (c == 'n')
		return (pf_write_data(pf, vl, res));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		valist;
	t_printf	*pf;
	int			res;

	va_start(valist, format);
	res = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			pf = pf_parse(&format, &valist);
			if (!pf)
				return (-1);
			res += put_printf(pf, &valist, res);
			free(pf);
		}
		else
		{
			ft_putchar(*format++);
			res++;
		}
	}
	return (res);
}
