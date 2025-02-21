/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlu <eunlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:18:18 by eunlu             #+#    #+#             */
/*   Updated: 2025/02/21 20:22:29 by eunlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_print_pid(t_pid pid)
{
	char	ch;

	if (pid > 9)
	{
		ft_print_pid(pid / 10);
		ft_print_pid(pid % 10);
	}
	else
	{
		ch = pid + '0';
		write(1, &ch, 1);
	}
}

static void	ft_get_char(int signal)
{
	static char	ch = 0;
	static int	i = 0;

	ch = ch << 1;
	if (signal == SIGUSR1)
		ch |= 1;
	i++;
	if (i == 8)
	{
		write(1, &ch, 1);
		ch = 0;
		i = 0;
	}
}

int	main(void)
{
	t_pid	pid;

	pid = getpid();
	ft_print_pid(pid);
	write(1, "\n", 1);
	signal(SIGUSR1, ft_get_char);
	signal(SIGUSR2, ft_get_char);
	while (1)
		pause();
	return (0);
}
