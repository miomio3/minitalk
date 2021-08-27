#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define BUFF_SIZE	7
#define ERROR		-1

static void	signal_handle(int signal);
size_t		ft_strlen(char *s);
static void	ft_putstr(char *s);
char		*ft_itoa(int pid);
void		ft_bzero(char *buf, size_t len);
int	ft_atoi_plus(char *argv);

int	g_signal;

static void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
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

static void	signal_handle(int signal)
{
	g_signal = signal;
}

static int read_pid(void)
{
	int		fd;
	char	buf[BUFF_SIZE + 1];

	fd = open("signal.txt", O_RDONLY);
	if(fd == -1)
		return(ERROR);
	ft_bzero(buf, BUFF_SIZE + 1);
	read(fd, buf, BUFF_SIZE);
	ft_putstr(buf);
	return(ft_atoi_plus(buf));
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
	g_signal = 0;
	receive();
	if(g_signal != SIGUSR1)
		return(ERROR);
	pid_c = read_pid();
	if(pid_c == ERROR)
		return(ERROR);
	if(kill(pid_c, SIGUSR1) == -1)
		return(ERROR);
	return(0);
}