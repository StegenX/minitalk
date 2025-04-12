/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagharbi <aagharbi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:53:18 by aagharbi          #+#    #+#             */
/*   Updated: 2024/11/15 18:19:48 by aagharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);

size_t	ft_putchar(char c);

size_t	ft_put_hex_lower(unsigned long long n);

size_t	ft_put_hex_upper(unsigned long long n);

size_t	ft_putnbr(int n);

size_t	ft_putnbr_unsigned(unsigned int n);

size_t	ft_put_pointer(unsigned long long n);

size_t	ft_putstr(char *s);

#endif
