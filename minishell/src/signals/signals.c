#include "../includes/minishell.h"

/*
When waiting for user input (in prompt)

When executing a child process (like running ls)

When in a heredoc (<<)
*/
void	handler(int num)
{
	(void)num;
	ft_putstr_fd("\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
/* Signals must be handled in 3 positions and modes,
first: when nothing input. ctrl+c & ctr + \,  will make new line.
second: something is written in the line, ctrl+c will do new line, ctr+\
will be ignored, ctr+d will be ignored.
third: when processing, execve.
last: from << herdoc, EOF signal*/
void	start_signal(void)
{
	struct sigaction	sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	
	// this will ignore the crtrl + \ like bash
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	
}
