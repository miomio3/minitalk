#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define BUFF_SIZE	100
#define ERROR		-1

void				ft_bzero(void *buf, size_t len);
void				ft_putstr(char *s);
void				receive_one(char buf[BUFF_SIZE + 1], int pid_c);
char				*ft_itoa(int pid);
unsigned	char	receive_char(pid_t pid_c);
void				easy_signal_handle(int signal);
unsigned char		receive_char(pid_t pid_c);

void	ft_putstr2(char *buf, int pid_c, size_t i)
{
	if(i + 1 % BUFF_SIZE == 0 && i != 1)
	{
		ft_putstr(buf);
		ft_bzero(buf, BUFF_SIZE);
		kill(pid_c, SIGUSR1);
	}
}

void	putpid(void)
{
	char	*pid_char;

	pid_char = ft_itoa(getpid());
	ft_putstr(pid_char);
	write(1, "\n", 1);
	free(pid_char);
}

void	short_len(int pid_c)
{
	usleep(50);
	kill(pid_c, SIGUSR1);
}