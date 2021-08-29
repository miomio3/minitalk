#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define BUFF_SIZE	1000
#define ERROR		-1
#define BIT_SIZE	8

int						ft_atoi_plus(char *argv);
static void				signal_handle(int signal);
size_t					ft_strlen(char *s);
char					*ft_itoa(int pid);
unsigned char			receive_char(pid_t pid_c);

int	g_signal;

static void	signal_handle(int signal)
{
	g_signal = signal;
}

static void	receive(void)
{
	g_signal = 0;
	while(1)
	{
		signal(SIGUSR1, signal_handle);
		signal(SIGUSR2, signal_handle);
		if(g_signal == SIGUSR1 || g_signal == SIGUSR2)
			break;
		pause();
	}
}

static int	send_char(pid_t pid_s, char *s)
{
	unsigned char	uc;
	size_t			i;
	int				bit;
	int				si;

	si = 0;
	while(1)
	{
		uc = (unsigned char)s[si];
		i = 0;
		if(si == BUFF_SIZE + 1)
		{
			receive();
			usleep(50);
		}
		usleep(100);
		while(i < BIT_SIZE)
		{
			bit = (uc >> i++) & 1;
			usleep(20);
			if(kill(pid_s, SIGUSR1 + bit) == -1)
				return(ERROR);
			if(i == BIT_SIZE)
				break;
			receive();
		}
		if(s[si] == '\0')
			break;
		si++;
	}
	return(0);
}

int	main(int argc, char *argv[])
{
	int		pid_s;

	if(argc != 3)
		return(-1);
	pid_s = ft_atoi_plus(argv[1]);
	if(pid_s == ERROR)
	{
		kill(pid_s, SIGUSR2);
		return(ERROR);
	}
	if(kill(pid_s, SIGUSR1) == -1)//1回目送信
		return(ERROR);
	receive();//1回目受信
	if(g_signal != SIGUSR1)
		return(ERROR);
	send_char(pid_s, argv[2]);
	return(0);
}
