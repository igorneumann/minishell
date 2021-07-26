#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ft_hola(int sig)
{
	printf("hola");
	//write(1, "\nServidor apagado.\n", 26);
	sig = 2;
}

int		main()
{
	signal(SIGINT, ft_hola);
	while (1)
	{

	}
	return(0);
}
