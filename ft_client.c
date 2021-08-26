#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

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
	while(j < i)
	{
		a = a * 10;
		a = a + argv[j] - '0';
		j++;
	}
	return (a);
}

int	main(int argc, char *argv[])
{
	short 	p;
	//int		i;

	p = '1';
	int	pid = ft_atoi_plus(argv[1]);
	if(argc > 2)
		return(-1);
	/* while(i < 4096)
	{
		if(p % 2 == 0) */
			printf("%d\n", kill(pid, SIGUSR1));

		/* else if(p % 2 == 1) */
			
		/* p = p / 2;
		i++; */
	
	return(0);
}