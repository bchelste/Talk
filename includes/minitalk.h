/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:00:21 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/22 00:05:47 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

# define BUFF 1024

typedef struct s_server
{
	int				counter;
	int				nbr;
	int				res;
	unsigned char	symbol;
	unsigned char	*arr;
	pid_t			pid_client;
}					t_server;

int		ft_strlen(unsigned char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(unsigned char *str, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);

#endif