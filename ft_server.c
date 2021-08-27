#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define BUFF_SIZE	7
#define ERROR		-1

static void	signal_handle(int signal, siginfo_t *info_c, void *ucontext);
size_t		ft_strlen(char *s);
static void	ft_putstr(char *s);
char		*ft_itoa(int pid);
void		ft_bzero(void *buf, size_t len);
int			ft_atoi_plus(char *argv);

typedef struct g_siginfo
{
	int			g_signal;
	siginfo_t	g_siginfot;
}g_siginfo;

g_siginfo info;

static void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}

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

int	main(void)
{
	char 	*pid_char;
	int		pid_c;

	pid_char = ft_itoa(getpid());
	if(pid_char == NULL)
		return(ERROR);
	ft_putstr(pid_char);
	free(pid_char);
	receive();
	if(info.g_signal != SIGUSR1)
		return(ERROR);
	pid_c = info.g_siginfot.si_pid;
	while(1)
	/* if(pid_c == ERROR)
		return(ERROR);
	if(kill(pid_c, SIGUSR1) == -1)
		return(ERROR); */
	return(0);
}