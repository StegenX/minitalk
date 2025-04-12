/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagharbi <aagharbi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:32:53 by aagharbi          #+#    #+#             */
/*   Updated: 2025/02/08 13:33:16 by aagharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int		g_handler;

void	handler(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("Message Recived !!\n");
	else if (sig == SIGUSR2)
		g_handler = 1;
}

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr++ == '-')
			sign = -1;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		nb = nb * 10 + (*nptr - 48);
		nptr++;
	}
	return (nb * sign);
}

void	send_null(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
		i++;
		usleep(100);
	}
}

void	send_signal(int PID, char *message)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	while (message[i++])
	{
		c = message[i - 1];
		j = 0;
		while (j++ < 8)
		{
			if ((c >> (j - 1)) & 1)
			{
				if (kill(PID, SIGUSR2) == -1)
					exit((write(2, "Invalid PID\n", 12), 1));
			}
			else if (kill(PID, SIGUSR1) == -1)
				exit((write(2, "Invalid PID\n", 12), 1));
			while (!g_handler)
				;
			g_handler = 0;
		}
	}
	send_null(PID);
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		write(2, "Invalid PID\n", 12);
		return (0);
	}
	send_signal(pid, av[2]);
}
