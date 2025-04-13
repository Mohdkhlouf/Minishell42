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
first: when nothing input. it will make new line.
second: with processing child, or something is written in the line.
thirsd: from << herdoc, EOF signal*/
void	start_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
