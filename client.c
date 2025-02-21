#include "minitalk.h"

static int	pid_to_int(const char *str)
{
	int	i;
	int	sign;
	int result;

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

	i = 0;
	while (i < 8)
	{
		if (c & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c = c >> 1;
		i++;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	i = 0;
	if (argc != 3)
	{
		write(1, "Usage: ./client [PID] [message]\n", 31);
		return (1);
	}
	pid = pid_to_int(argv[1]);
	while (argv[2][i])
	{
		ft_send_char(pid, argv[2][i]);
		i++;
	}
	return (0);
}
