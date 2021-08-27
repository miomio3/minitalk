#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define BUFF_SIZE	7
#define ERROR		-1

int	ft_atoi_plus(char *argv);
static void	signal_handle(int signal);
size_t	ft_strlen(char *s);
char	*ft_itoa(int pid);

int	g_signal;

static void	signal_handle(int signal)
{
	g_signal = signal;
}

static void	receive(void)
{
	while(1)
	{
		signal(SIGUSR1, signal_handle);
		signal(SIGUSR2, signal_handle);
		if(g_signal == SIGUSR1 || g_signal == SIGUSR2)
			break;
		pause();
	}
}

static int	write_pid(void)
{
	int		fd;
	char	*pid_char;

	fd = open("signal.txt", O_WRONLY);
	if(fd == -1)
		return(ERROR);
	pid_char = ft_itoa(getpid());
	write(fd, pid_char, ft_strlen(pid_char));
	return(0);
}

int	main(int argc, char *argv[])
{
	int		pid_s;

	if(argc != 2)
		return(-1);
	pid_s = ft_atoi_plus(argv[1]);
	if(pid_s == ERROR)
	{
		kill(pid_s, SIGUSR2);
		return(ERROR);
	}
	if(write_pid() == ERROR)
		return(ERROR);
	if(kill(pid_s, SIGUSR1) == -1)
		return(ERROR);
	receive();
	if(g_signal != SIGUSR1)
		return(ERROR);
	printf("g_signal = %d", g_signal);//debug
	return(0);
}
