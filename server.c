#include "minitalk.h"

static void	ft_print_pid(pid_t pid)
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
	static char	ch;
	static int	i = 0;

	if (signal == SIGUSR1)
		ch |= 1;
	i++;
	if (i == 8)
	{
		write(1, &ch, 1);
		ch = 0;
		i = 0;
	}
	ch = ch << i;
}

int main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_print_pid(pid);
	write(1, "\n", 1);
	signal(SIGUSR1, ft_get_char);
	signal(SIGUSR2, ft_get_char);
	while (1)
		pause();
	return (0);
}

