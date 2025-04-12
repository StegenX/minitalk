/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagharbi <aagharbi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:14:12 by aagharbi          #+#    #+#             */
/*   Updated: 2024/11/15 11:18:21 by aagharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putnbr_unsigned(unsigned int n)
{
	size_t	count;

	count = 0;
	if (n > 9)
		count += ft_putnbr_unsigned((n / 10));
	count += ft_putchar((n % 10) + '0');
	return (count);
}
