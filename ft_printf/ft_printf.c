/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagharbi <aagharbi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:42:17 by aagharbi          #+#    #+#             */
/*   Updated: 2024/11/21 09:51:41 by aagharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	check_format_hp(va_list args, const char *format)
{
	size_t	count;
	int		i;
	int		a;
	void	*hptr;

	i = 0;
	count = 0;
	hptr = &a;
	if (format[i + 1] == 'X')
	{
		*(unsigned long long *)hptr = va_arg(args, unsigned long long);
		count += ft_put_hex_upper(*(unsigned long long *)hptr);
	}
	else if (format[i + 1] == 'x')
	{
		*(unsigned long long *)hptr = va_arg(args, unsigned long long);
		count += ft_put_hex_lower(*(unsigned long long *)hptr);
	}
	else if (format[i + 1] == 'p')
	{
		*(unsigned long long *)hptr = va_arg(args, unsigned long long);
		count += ft_put_pointer(*(unsigned long long *)hptr);
	}
	return (count);
}

static size_t	check_format_int(va_list args, const char *format)
{
	size_t	count;
	int		i;
	int		a;
	void	*iptr;

	i = 0;
	count = 0;
	iptr = &a;
	if (format[i + 1] == 'd' || format[i + 1] == 'i')
	{
		*(int *)iptr = va_arg(args, int);
		count += ft_putnbr(*(int *)iptr);
	}
	else if (format[i + 1] == 'u')
	{
		*(unsigned int *)iptr = va_arg(args, unsigned int);
		count += ft_putnbr_unsigned(*(unsigned int *)iptr);
	}
	else
		count += check_format_hp(args, &format[i]);
	return (count);
}

static size_t	check_format(va_list args, const char *format)
{
	size_t	count;
	int		i;
	char	*tmp;
	int		a;
	void	*ptr;

	i = 0;
	count = 0;
	ptr = &a;
	if (format[i + 1] == 's')
	{
		tmp = va_arg(args, char *);
		ptr = tmp;
		count += ft_putstr((char *)ptr);
	}
	else if (format[i + 1] == 'c')
	{
		*(int *)ptr = va_arg(args, int);
		count += ft_putchar(*(int *)ptr);
	}
	else if (format[i + 1] == '%')
		count += ft_putchar('%');
	else
		count += check_format_int(args, &format[i]);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	size_t	i;
	va_list	args;
	size_t	count;

	if (!format)
		return (-1);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += check_format(args, &format[i]);
			i += 2;
		}
		else
		{
			write(1, &format[i], 1);
			i++;
			count++;
		}
	}
	va_end(args);
	return (count);
}
