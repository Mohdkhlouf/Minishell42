/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:11:39 by akumari           #+#    #+#             */
/*   Updated: 2025/05/21 13:12:05 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_signal_rest(t_data *data)
{
	int	new_stdin;

	new_stdin = 0;
	if (g_signal_status == 1)
	{
		g_signal_status = 0;
		data->exit_code = 130;
		new_stdin = open("/dev/tty", O_RDONLY);
		if (new_stdin >= 0)
		{
			dup2(new_stdin, STDIN_FILENO);
			close(new_stdin);
		}
	}
}

void	handler(int num)
{
	if (num == SIGINT)
	{
		g_signal_status = 130;
		if (!rl_done)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	set_prompt_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
