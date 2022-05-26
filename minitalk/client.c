/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:59:03 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/22 00:42:21 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	create_signal(unsigned char symbol, int pid_server)
{
	int		i;
	int		sgnl;

	i = 0;
	while (i < 8)
	{
		sgnl = symbol % 2;
		if (sgnl == 0)
			kill(pid_server, SIGUSR2);
		else
			kill(pid_server, SIGUSR1);
		usleep(200);
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
}

int	main(int argc, char **argv)
{
	int					pid;

	if (argc != 3)
	{
		ft_putstr_fd((unsigned char *)"The wrong number of arguments!\n", 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	ft_send(pid, argv[2]);
	ft_putchar_fd('\n', 1);
	return (0);
}
