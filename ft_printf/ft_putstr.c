/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagharbi <aagharbi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:08:46 by aagharbi          #+#    #+#             */
/*   Updated: 2024/11/15 16:17:17 by aagharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putstr(char *s)
{
	size_t	count;

	count = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		count = 6;
		return (count);
	}
	while (*s)
	{
		write(1, s, 1);
		s++;
		count++;
	}
	return (count);
}
