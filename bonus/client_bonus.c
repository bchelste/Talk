/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:46:38 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/22 00:04:52 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

static void	ft_sig_back(int sgnl, siginfo_t *siginfo, void *ptr)
{
	static int	counter;

	ptr = NULL;
	siginfo = NULL;
	if (sgnl == SIGUSR1)
		counter++;
	else if (sgnl == SIGUSR2)
	{
		counter++;
		ft_putstr_fd((unsigned char *)"confirm signal was received back\n", 1);
		ft_putstr_fd((unsigned char *)"signal from server:", 1);
		ft_putnbr_fd(counter, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

static void	create_signal(unsigned char symbol, int pid_server)
{
	int		i;
	int		sgnl;

	i = 0;
	while (i < 8)
	{
		sgnl = symbol % 2;
		usleep(100);
		if (sgnl == 0)
			kill(pid_server, SIGUSR2);
		else
			kill(pid_server, SIGUSR1);
		usleep(5000);
		symbol = symbol / 2;
		i++;
	}
}

static void	ft_send(int pid_server, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		create_signal((unsigned char)src[i], pid_server);
		i++;
	}
	create_signal('\0', pid_server);
	usleep(500);
}

void	ft_init_sigaction(struct sigaction *sigact)
{
	sigemptyset(&sigact->sa_mask);
	sigact->sa_sigaction = ft_sig_back;
	sigact->sa_flags = SA_SIGINFO;
	sigaddset(&sigact->sa_mask, SIGUSR1);
	sigaddset(&sigact->sa_mask, SIGUSR2);
	sigaction(SIGUSR1, sigact, NULL);
	sigaction(SIGUSR2, sigact, NULL);
}

int	main(int argc, char **argv)
{
	struct sigaction	sigact;
	int					pid;

	if (argc != 3)
	{
		ft_putstr_fd((unsigned char *)"The wrong number of arguments!\n", 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	ft_init_sigaction(&sigact);
	ft_send(pid, argv[2]);
	ft_putchar_fd('\n', 1);
	return (0);
}
