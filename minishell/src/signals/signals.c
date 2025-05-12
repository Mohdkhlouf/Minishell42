#include "../includes/minishell.h"

/*
When waiting for user input (in prompt)

When executing a child process (like running ls)

When in a heredoc (<<)
*/


void heredoc_signal_rest(t_data *data)
{
	int new_stdin;

	new_stdin = 0;
	if (g_signal_status)
	{
		g_signal_status = 0;
		data->exit_code = 130;
		new_stdin = open("/dev/tty", O_RDONLY);
		if (new_stdin >= 0)
			dup2(new_stdin, STDIN_FILENO);
	}
}

void handler(int num)
{
	(void)num;
	// g_signal_status = 130;
	ft_putstr_fd("\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void set_prompt_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = handler; // Your custom handler for prompt
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN; // Ignore Ctrl+
	sigaction(SIGQUIT, &sa, NULL);
}

void set_child_signals(void)
{
	signal(SIGINT, SIG_DFL);  // Default behavior for Ctrl+C
	signal(SIGQUIT, SIG_DFL); // Default behavior for Ctrl+
}
