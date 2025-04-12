/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex_upper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagharbi <aagharbi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:18:52 by aagharbi          #+#    #+#             */
/*   Updated: 2024/11/16 09:34:47 by aagharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_put_hex_upper(unsigned long long n)
{
	unsigned long long	rem;
	char				hex[20];
	int					i;
	size_t				count;

	i = 0;
	count = 0;
	if (n == 0)
		return (count += ft_putchar('0'));
	while (n > 0)
	{
		rem = n % 16;
		n /= 16;
		if (rem < 10)
			hex[i++] = rem + '0';
		else
			hex[i++] = 'A' + (rem - 10);
	}
	while (--i >= 0)
	{
		write(1, &hex[i], 1);
		count++;
	}
	return (count);
}
