/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagharbi <aagharbi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:11:00 by aagharbi          #+#    #+#             */
/*   Updated: 2024/11/15 15:31:44 by aagharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_put(char *hex, int i)
{
	size_t	count;

	count = 0;
	write (1, "0x", 2);
	count += 2;
	while (--i >= 0)
	{
		write(1, &hex[i], 1);
		count++;
	}
	return (count);
}

size_t	ft_put_pointer(unsigned long long n)
{
	unsigned long long	rem;
	char				hex[20];
	int					i;
	size_t				count;

	i = 0;
	count = 0;
	if (!n)
	{
		write(1, "(nil)", 5);
		count = 5;
		return (count);
	}
	while (n > 0)
	{
		rem = n % 16;
		n /= 16;
		if (rem < 10)
			hex[i++] = rem + '0';
		else
			hex[i++] = 'a' + (rem - 10);
	}
	return (count += ft_put(hex, i));
}
