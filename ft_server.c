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

static void				signal_handle(int signal, siginfo_t *info_c, void *ucontext);
size_t					ft_strlen(char *s);
void					ft_putstr(char *s);
char					*ft_itoa(int pid);
void					ft_bzero(void *buf, size_t len);
int						ft_atoi_plus(char *argv);
unsigned char			receive_char(pid_t pid_c);
static void				easy_signal_handle(int signal);
void					ft_putstr2(char *buf, int pid_c);
void					putpid(void);
void					receive_one(char buf[BUFF_SIZE + 1], int pid_c);
void					short_len(int pid_c);

typedef struct g_siginfo
{
	int			g_signal;
	siginfo_t	g_siginfot;
	char		buf[BUFF_SIZE + 1];
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

void	easy_signal_handle(int signal)
{
	info.g_signal = signal;
}

unsigned	char receive_char(pid_t pid_c)
{
	size_t			i;
	unsigned char	c;
	int				bit;

	i = 0;
	c = 0;
	while(i < BIT_SIZE)
	{
		info.g_signal = 0;
		short_len(pid_c);//1回目送信
		while(1)
		{
			signal(SIGUSR1, easy_signal_handle);
			signal(SIGUSR2, easy_signal_handle);
			if(info.g_signal == SIGUSR1 || info.g_signal == SIGUSR2)
				break;
			pause();
		}
		bit = (info.g_signal - SIGUSR1) << i++;
		c = c + bit;
	}
	return(c);
}

int	main(void)
{
	int				pid_c;
	size_t			i;
	unsigned char	c;
	
	putpid();
	ft_bzero(info.buf, BUFF_SIZE + 1);
	while(1)
	{
		receive();//1回目受信
		if(info.g_signal != SIGUSR1)
			return(ERROR);
		pid_c = info.g_siginfot.si_pid;
		i = 0;
		while(1)
		{
			c = receive_char(pid_c);
			info.buf[i++] = c;
			if(c == '\0')
			{
				ft_putstr(info.buf);
				write(1, "\n", 1);
				break;
			}
			if(i == BUFF_SIZE)
			{
				ft_putstr2(info.buf, pid_c);
				i = 0;
			}
		}
	}
	return(0);
}