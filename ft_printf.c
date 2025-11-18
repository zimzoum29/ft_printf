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
	if (!str)
		return (ft_putstr("(null)"));
	while(str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
		return (ft_putstr("-2147483648"));
	if (nb < 0)
	{
		len += ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
		len += ft_putnbr(nb / 10);
	len += ft_putchar(nb % 10 + '0');
	return (len);
}


int	ft_putunsigned_nbr(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb > 9)
		len += ft_putunsigned_nbr(nb / 10);
	len += ft_putchar(nb % 10 + '0');
	return (len);
}

int	ft_putnbr_base(unsigned long nb, char *base, int len)
{
	unsigned long	len_base;

	len_base = ft_strlen(base);
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
	{
		len += ft_putstr("0x");
		len += ft_putnbr_base(va_arg(args, unsigned long),"0123456789abcdef", len);
	}
	else if (c == 'd' || c == 'i')
		len = ft_putnbr(va_arg(args, int));
	else if (c == 'u')
    	len = ft_putunsigned_nbr(va_arg(args, unsigned int));
	else if (c == 'x')
		len = ft_putnbr_base(va_arg(args, unsigned int),"0123456789abcdef", len);
	else if (c == 'X')
		len = ft_putnbr_base(va_arg(args, unsigned int),"0123456789ABCDEF", len);

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
		if (str[i] == '%')
		{
			tmp = ft_check_case(str[i + 1], args);
			if (tmp == -1)
				return (-1);
			len += tmp;
			i++;
		}
		else
		{
			len += ft_putchar(str[i]);
		}
		i++;
	}
	va_end(args);
	return (len);
}
