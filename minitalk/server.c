/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:59:18 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/22 00:36:04 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_set_serv(t_server **serv)
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
				free(*serv);
				(*serv) = NULL;
				return ;
			}
		}
		(*serv)->symbol = 0;
		(*serv)->counter = 0;
	}
}

static void	ft_receive(int sgnl)
{
	static t_server	*serv;
	unsigned int	bit;

	if (serv == NULL)
		ft_set_serv(&serv);
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
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putstr_fd((unsigned char *)("server started\nserver PID: "), 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	while (1)
	{
		signal(SIGUSR1, ft_receive);
		signal(SIGUSR2, ft_receive);
		usleep(50);
	}
	return (0);
}
