/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:35:30 by kamin             #+#    #+#             */
/*   Updated: 2022/03/02 02:59:48 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void	action(int sig, siginfo_t *info, void *context)
{
	static unsigned int		bit;
	static int				multiplier;

	(void)context;
	if (multiplier > 0)
		bit <<= 1;
	if (sig == SIGUSR1)
		bit++;
	multiplier++;
	if (multiplier == 8)
	{
		write(1, &bit, 1);
		multiplier = 0;
		bit = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	signal;

	signal.sa_flags = SA_SIGINFO;
	signal.sa_sigaction = action;
	printf("Server Started!\n");
	printf("PID: %d\n", getpid());
	printf("Waiting for message...\n");
	sigaction(SIGUSR1, &signal, NULL);
	sigaction(SIGUSR2, &signal, NULL);
	while (1)
	{
	}
	return (0);
}
