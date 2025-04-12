/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagharbi <aagharbi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:17:19 by aagharbi          #+#    #+#             */
/*   Updated: 2024/11/16 09:29:48 by aagharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putnbr(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	if (n < 0)
	{
		if (n == -2147483648)
		{
			count += ft_putstr("-2147483648");
			return (count);
		}
		write(1, "-", 1);
		count++;
		n = -n;
	}
	if (n > 9)
		count += ft_putnbr(n / 10);
	count += ft_putchar((n % 10) + '0');
	return (count);
}
