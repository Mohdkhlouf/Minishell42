#include "../includes/minishell.h"

void	write_free_heredoc(int fd, char *to_write, char *line)
{
	write(fd, to_write, ft_strlen(to_write));
	write(fd, "\n", 1);
	free(to_write);
	free(line);
}

void	set_g_signal(int value)
{
	g_signal_status = value;
}

void	reset_signals_to_prompt(void)
{
	set_prompt_signals(); 
}

void	handle_heredoc_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = SIGINT;
	}
}

int	heredoc_event_hook(void)
{
	if (g_signal_status)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}
