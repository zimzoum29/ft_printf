/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigondra <tigondra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:08:16 by tigondra          #+#    #+#             */
/*   Updated: 2025/11/20 14:12:32 by tigondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned long nb, char *base, int len)
{
	unsigned long	len_base;

	len_base = ft_strlen(base);
	if (len == -1)
	{
		if (nb == 0)
		{
			len = ft_putstr("(nil)");
			return (len);
		}
		len = ft_putstr("0x");
	}
	if (nb >= len_base)
	{
		len = ft_putnbr_base(nb / len_base, base, len);
		write(1, &base[nb % len_base], 1);
		len++;
	}
	else
	{
		write(1, &base[nb], 1);
		len++;
	}
	return (len);
}

int	ft_check_case(char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = ft_putchar(va_arg(args, int));
	else if (c == 's')
		len = ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		len += ft_putnbr_base(va_arg(args, unsigned long), "0123456789abcdef",
				-1);
	else if (c == 'd' || c == 'i')
		len = ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		len = ft_putunsigned_nbr(va_arg(args, unsigned int));
	else if (c == 'x')
		len = ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef",
				len);
	else if (c == 'X')
		len = ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF",
				len);
	else if (c == '%')
		len = ft_putchar('%');
	else
		return (-1);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;
	int		tmp;

	if (!str)
		return (-1);
	i = -1;
	len = 0;
	va_start(args, str);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			tmp = ft_check_case(str[i + 1], args);
			if (tmp == -1)
				return (-1);
			len += tmp;
			i++;
		}
		else
			len += ft_putchar(str[i]);
	}
	va_end(args);
	return (len);
}
