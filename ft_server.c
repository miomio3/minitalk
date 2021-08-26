#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int	g_signal;

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while(s[i])
		i++;
	return(i);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

char	*ft_itoa(int pid)
{
	char	*pid_char;
	int		p;
	size_t	i;

	p = pid;
	i = 0;
	if(p != 0)
	{
		while (p)
		{
			p = p / 10;
			i++;
		}
	}
	else
		i = 1;
	pid_char = malloc(sizeof(char) * (i + 1));
	pid_char[i] = '\0';
	while(i > 0)
	{
		i--;
		pid_char[i] = '0' + pid % 10;
		pid = pid / 10;
	}
	return (pid_char);
}

void	signal_handle(int signal)
{
	printf("signal in handle = %d\n", signal);
	g_signal = signal;
}

int	main(void)
{
	int		pid;
	char 	*pid_char;
	short	p;
	size_t	i;

	pid = getpid();
	pid_char = ft_itoa(pid);
	ft_putstr(pid_char);
	write(1, "\n", 1);
	free(pid_char);
	i = 0;
	p = 0;
	while(i < 4096)
	{
		p = p * 2;
		signal(SIGUSR1, signal_handle);
		printf("%d\n", g_signal);
		fflush(stdout);
		signal(SIGUSR2, signal_handle);
		if(g_signal == SIGUSR2)
			p = p + 1;
		printf("%d", p);
		i++;
		pause();
	}
	return(0);
}