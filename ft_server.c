#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define BUFF_SIZE	7
#define ERROR		-1
#define BIT_SIZE	8

static void				signal_handle(int signal, siginfo_t *info_c, void *ucontext);
size_t					ft_strlen(char *s);
void					ft_putstr(char *s);
char					*ft_itoa(int pid);
void					ft_bzero(void *buf, size_t len);
int						ft_atoi_plus(char *argv);
static unsigned char	receive_char(pid_t pid_c);
static void	easy_signal_handle(int signal);

typedef struct g_siginfo
{
	int			g_signal;
	siginfo_t	g_siginfot;
}g_siginfo;

g_siginfo info;

static void	receive(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = *signal_handle;
	info.g_signal = 0;
	while(1)
	{
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		if(info.g_signal == SIGUSR1 || info.g_signal == SIGUSR2)
			break;
		pause();
	}
}

static void	signal_handle(int signal, siginfo_t *info_c, void *ucontext)
{
	info.g_signal = signal;
	info.g_siginfot = *info_c;
	if(ucontext == NULL)
		return;
}

static void	easy_signal_handle(int signal)
{
	info.g_signal = signal;
}

static unsigned	char receive_char(pid_t pid_c)
{
	size_t			i;
	unsigned char	c;
	int				bit;

	i = 0;
	while(i < BIT_SIZE)
	{
		info.g_signal = 0;
		usleep(10);
		kill(pid_c, SIGUSR1);//1回目送信
		while(1)
		{
			signal(SIGUSR1, easy_signal_handle);
			signal(SIGUSR2, easy_signal_handle);
			if(info.g_signal == SIGUSR1 || info.g_signal == SIGUSR2)
				break;
			pause();
		}
		bit = (info.g_signal - SIGUSR1) << i;
		c = c + bit;
		i++;
	}
	return(c);
}

int	main(void)
{
	char 	*pid_char;
	int		pid_c;
	char	c;

	pid_char = ft_itoa(getpid());
	if(pid_char == NULL)
		return(ERROR);
	ft_putstr(pid_char);
	free(pid_char);
	receive();//1回目受信
	if(info.g_signal != SIGUSR1)
		return(ERROR);
	pid_c = info.g_siginfot.si_pid;
	c = '1';
	while(c)
	{
		c = receive_char(pid_c);
		write(1, &c, 1);
	}
	return(0);
}