/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigondra <tigondra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:08:16 by tigondra          #+#    #+#             */
/*   Updated: 2025/11/18 16:38:40 by tigondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		i++;
	}
	return (i);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr(int nb, int len)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		len = 11;
		return (len);
	}
	if (nb < 0)
	{
		ft_putchar('-');
		len++;
		nb = -nb;
	}
	if (nb > 9)
		len += ft_putnbr(nb / 10, len);
	ft_putchar(nb % 10 + '0');
	len++;
	return (len);
}

int	ft_putunsigned_nbr(unsigned int nb, int len)
{
	if (nb > 9)
		len += ft_putnbr(nb / 10, len);
	ft_putchar(nb % 10 + '0');
	len++;
	return (len);
}

int	ft_putnbr_base(unsigned long nbr, char *base, int len)
{
	int			len_base;
	long int	nb;

	nb = nbr;
	len_base = ft_strlen(base);
	if (nb >= len_base)
	{
		len = ft_putnbr_base((nb / len_base), base, len);
		write(1, &base[nb % len_base], 1);
		len++;
	}
	if (nb < len_base)
	{
		write(1, &base[nb % len_base], 1);
		len ++;;
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
		len = ft_putnbr_base((unsigned long)va_arg(args, void *),"0123456789abcdef", len);
	else if (c == 'd' || c == 'i')
		len = ft_putnbr(va_arg(args, int), len);
	else if (c == 'u')
	{
		write(1, "0x", 2);
		len = ft_putunsigned_nbr(va_arg(args, unsigned int), len) + 2;
	}
	else if (c == 'x')
		len = ft_putnbr_base(va_arg(args, int),"0123456789abcdef", len);
	else if (c == 'X')
		len = ft_putnbr_base(va_arg(args, int),"0123456789ABCDEF", len);
	else if (c == '%')
		len = ft_putchar('%');
	else
		return (-1);
	return (len);
}

int     ft_printf(const char *str, ...)
{
	va_list args;
	int     i;
	int	len;
	int	tmp;

	i = 0;
	len = 0;
	va_start(args, str);
	while(str[i])
	{
		if(str[i] == '%')
		{
			tmp = ft_check_case(str[i + 1], args);
			if (tmp == -1)
				return (-1);
			len += tmp - 1;
			i++;
		}
		else
			ft_putchar(str[i]);
		len++;
		i++;
	}
	va_end(args);
	return (len);
}

// int	main(void)
// {
// 	void *r = "strstrrrrr";
// 	ft_printf("%d\n", ft_printf("testtest %c\n%s\n%i%%\n%p\n%u\n%x\n%X\n", '1', "aaa", 100, r, 429496, 42, 42));
// 	printf("%d\n", printf("testtest %c\n%s\n%i%%\n%p\n%u\n%x\n%X\n", '1', "aaa", 100, r, 429496, 42, 42));
// }