/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:30:15 by kamin             #+#    #+#             */
/*   Updated: 2022/03/02 03:54:17 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static size_t	g_char_count = 0;

static int	ft_atoi(const char *str)
{
	int	final;
	int	sign;

	final = 0;
	sign = 1;
	while (*str == '\t' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == '\n' || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str > 47 && *str < 58)
	{
		final = (final * 10) + *str - 48;
		str++;
	}
	return (final * sign);
}

static size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	increase_count(int sig)
{
	(void)sig;
	g_char_count++;
}

static void	send_char(unsigned char c, int p_id)
{
	unsigned char	bit;
	int				i;
	int				and;

	i = 0;
	bit = 0b10000000;
	while (i < 8)
	{
		and = bit & c;
		if (and)
			kill(p_id, SIGUSR1);
		else
			kill(p_id, SIGUSR2);
		usleep(100);
		bit >>= 1;
		i++;
	}
}

int	main(int ac, char *av[])
{
	int					p_id;
	struct sigaction	signal;
	size_t				mess_size;

	signal.sa_handler = increase_count;
	mess_size = 1;
	sigaction(SIGUSR1, &signal, NULL);
	if (ac > 1)
		p_id = ft_atoi(av[1]);
	if (ac == 3)
	{
		mess_size = ft_strlen(av[2]);
		while (*av[2] && g_char_count != mess_size)
		{
			send_char(*av[2], p_id);
			av[2]++;
		}
		if (mess_size == g_char_count)
			write(1, "Message sent succefully!\n", 25);
	}
	return (0);
}
