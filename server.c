/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagharbi <aagharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:39:38 by aagharbi          #+#    #+#             */
/*   Updated: 2025/03/13 16:52:21 by aagharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <unistd.h>

static void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static char	c;
	static int	bit_count;

	context = NULL;
	if (signum == SIGUSR1)
		c |= (0 << bit_count);
	else if (signum == SIGUSR2)
		c |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &c, 1);
		c = 0;
		bit_count = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
