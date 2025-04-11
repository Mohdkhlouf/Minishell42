#include "../includes/minishell.h"

void handler(int num)
{
	(void) num;
	printf("test\n");
}

void	start_signal(void)
{
	struct sigaction sa;
	sa.sa_handler = handler;

	sigaction(SIGINT, &sa , NULL);

	printf("SIgnal starting Here!!\n");
}
