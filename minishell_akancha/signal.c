#include "main.h"

void handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	// rl_replace_line("", 0);
	printf("\33[2K\r");
	rl_on_new_line();
	rl_redisplay();
}

void handle_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}
