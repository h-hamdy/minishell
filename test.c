// CPP program to illustrate
// default Signal Handler
#include<stdio.h>
#include<signal.h>

int main()
{
	signal(SIGINT, handle_sigint);
	while (1)
	{
		printf("hello world\n");
		sleep(1);
	}
	return 0;
}
