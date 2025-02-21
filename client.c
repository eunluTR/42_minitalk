/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlu <eunlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:18:06 by eunlu             #+#    #+#             */
/*   Updated: 2025/02/21 20:33:21 by eunlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	pid_to_int(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

static void	ft_send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(5000);
	}
}

int	main(int argc, char **argv)
{
	t_pid	pid;
	int		i;

	i = 0;
	if (argc != 3)
	{
		write(1, "Usage: ./client [PID] [message]\n", 31);
		return (1);
	}
	pid = pid_to_int(argv[1]);
	if (pid < 0)
	{
		write(1, "Error: PID is incorrect.\n", 26);
		return (1);
	}
	while (argv[2][i])
	{
		ft_send_char(pid, argv[2][i]);
		i++;
	}
	return (0);
}
