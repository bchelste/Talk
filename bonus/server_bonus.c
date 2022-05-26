/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:39:39 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/22 00:12:17 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_set_serv(t_server **serv, siginfo_t *siginfo)
{
	int	i;

	i = 0;
	*serv = (t_server *)malloc(sizeof(t_server));
	(*serv)->arr = (unsigned char *)malloc(sizeof(unsigned char) * BUFF);
	while (i < BUFF)
	{
		(*serv)->arr[i] = '\0';
		i++;
	}
	(*serv)->counter = 0;
	(*serv)->res = 0;
	(*serv)->symbol = 0;
	(*serv)->nbr = 0;
	(*serv)->pid_client = siginfo->si_pid;
}

static void	ft_receive_utils(t_server **serv)
{
	if ((*serv)->counter > 7)
	{
		(*serv)->arr[(*serv)->nbr] = (*serv)->symbol;
		(*serv)->nbr++;
		(*serv)->res = (*serv)->res + (*serv)->counter;
		if (((*serv)->nbr == (BUFF - 2)) || ((*serv)->symbol == '\0'))
		{
			(*serv)->arr[(*serv)->nbr + 1] = '\0';
			ft_putstr_fd((*serv)->arr, 1);
			(*serv)->nbr = 0;
			if ((*serv)->symbol == '\0')
			{
				ft_putchar_fd('\n', 1);
				ft_putstr_fd((unsigned char *)"sgnl reseived from client:", 1);
				ft_putnbr_fd((*serv)->res, 1);
				ft_putchar_fd('\n', 1);
				kill((*serv)->pid_client, SIGUSR2);
				free(*serv);
				(*serv) = NULL;
				return ;
			}
		}
		(*serv)->symbol = 0;
		(*serv)->counter = 0;
	}
}

static void	ft_receive(int sgnl, siginfo_t *siginfo, void *ptr)
{
	static t_server	*serv;
	unsigned int	bit;

	ptr = NULL;
	if (siginfo->si_pid == 0)
		return ;
	if (serv == NULL)
		ft_set_serv(&serv, siginfo);
	if (sgnl == SIGUSR2)
		bit = 0;
	else if (sgnl == SIGUSR1)
		bit = 1;
	else
		return ;
	serv->symbol = serv->symbol + (bit << serv->counter);
	serv->counter++;
	ft_receive_utils(&serv);
	usleep(50);
	if (serv)
		kill(serv->pid_client, SIGUSR1);
}

static void	ft_init_sigaction(struct sigaction *sigact)
{
	sigemptyset(&sigact->sa_mask);
	sigact->sa_sigaction = ft_receive;
	sigact->sa_flags = SA_SIGINFO;
	sigaddset(&sigact->sa_mask, SIGUSR1);
	sigaddset(&sigact->sa_mask, SIGUSR2);
	sigaction(SIGUSR1, sigact, NULL);
	sigaction(SIGUSR2, sigact, NULL);
}

int	main(void)
{
	struct sigaction	sigact;	
	pid_t				pid;

	pid = getpid();
	ft_putstr_fd((unsigned char *)"server started\nserver PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	ft_init_sigaction(&sigact);
	while (1)
	{
		usleep(100);
	}
	return (0);
}
