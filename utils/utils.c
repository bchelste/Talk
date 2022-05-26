/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:59:51 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/20 23:48:26 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_strlen(unsigned char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(unsigned char *str, int fd)
{
	int	n;

	if (str == NULL)
		return ;
	n = ft_strlen(str);
	write(fd, str, n);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	res;

	res = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		res = -1;
	}
	if (n >= 10)
		ft_putnbr_fd((n / 10) * res, fd);
	ft_putchar_fd((n % 10) + 48, fd);
}

int	ft_atoi(const char *str)
{
	int		res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == 'v')
		|| (str[i] == 'r') || (str[i] == '\f') || (str[i] == ' '))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res * sign);
}
