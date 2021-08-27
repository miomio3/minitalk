#include <stdlib.h>
#include <limits.h>

#define ERROR	-1

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while(s[i])
		i++;
	return(i);
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

void	ft_bzero(char *buf, size_t len)
{
	size_t	i;

	i = 0;
	while(i < len)
	{
		buf[i] = 0;
		i++;
	}
}

int	ft_atoi_plus(char *argv)
{
	int	i;
	int	j;
	int	a;

	i = 0;
	a = 0;
	while(argv[i])
		i++;
	j = 0;
	if(argv[0] == '-')
		return(ERROR);
	while(j < i)
	{
		a = a * 10;
		a = a + argv[j] - '0';
		j++;
	}
	return(a);
}
