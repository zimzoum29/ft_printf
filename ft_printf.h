/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigondra <tigondra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:09:19 by tigondra          #+#    #+#             */
/*   Updated: 2025/11/20 13:58:51 by tigondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_strlen(char *str);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr(int nb);
int	ft_putunsigned_nbr(unsigned int nb);
int	ft_putnbr_base(unsigned long nbr, char *base, int len);
int	ft_check_case(char c, va_list args);
int	ft_printf(const char *str, ...) __attribute__((format(printf, 1, 2)));

#endif