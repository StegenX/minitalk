/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagharbi <aagharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:32:07 by aagharbi          #+#    #+#             */
/*   Updated: 2025/03/11 16:31:58 by aagharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <unistd.h>

int			g_null;

static void	handle_signal_server(int signum, siginfo_t *info, void *context)
{
	static char	c;
	static int	bit_count;

	context = NULL;
	if (signum == SIGUSR1)
	{
		c |= (0 << bit_count);
		g_null++;
	}
	else if (signum == SIGUSR2)
	{
		c |= (1 << bit_count);
		g_null = 0;
	}
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &c, 1);
		c = 0;
		bit_count = 0;
	}
	if (g_null == 8)
		kill(info->si_pid, SIGUSR1);
	else
		kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal_server;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
