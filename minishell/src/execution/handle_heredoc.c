#include "../includes/minishell.h"

void	reset_signals_to_prompt(void)
{
	set_prompt_signals(); // Reapply prompt signal handlers
}

static void	handle_heredoc_signals(int sig)
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

void	set_heredoc_signals(struct sigaction *sa_old)
{
	struct sigaction	new_sa;

	ft_memset(&new_sa, 0, sizeof(new_sa));
	new_sa.sa_handler = handle_heredoc_signals;
	new_sa.sa_flags = SA_RESTART;
	sigemptyset(&new_sa.sa_mask);
	if (sigaction(SIGINT, &new_sa, sa_old) == -1)
		return ;
}

int	handle_heredoc(char *input_delimiter, t_data *data, int expand)
{
	int					fd;
	char				*line;
	t_token				tmp_token;
	char				*to_write;
	t_token				*original_tokens;
	struct sigaction	sa_old;

	// int fd_in_copy
	// fd_in_copy = dup(STDIN_FILENO)
	fd = open("HEREDOC_TEMP.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	set_heredoc_signals(&sa_old);
	rl_event_hook = heredoc_event_hook;
	while (1)
	{
		line = readline("heredoc> ");
		if (g_signal_status)
		{
			free(line);
			free(input_delimiter);
			close(fd);
			unlink("HEREDOC_TEMP.txt");
			reset_signals_to_prompt();
			rl_event_hook = NULL;
			return (1);
		}
		if (!line)
			break ;
		if (!input_delimiter)
		{
			printf("heredoc: null delimiter\n");
			free(line);
			break ;
		}
		if (ft_strcmp(line, input_delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (expand == 1)
		{
			if (ft_strchr(line, '$'))
			{
				tmp_token.data = ft_strdup(line);
				tmp_token.type = TOK_STRING;
				original_tokens = data->tokens;
				data->tokens = &tmp_token;
				var_handler2(data, 0);
				to_write = ft_strdup(tmp_token.data);
				free(tmp_token.data);
				data->tokens = original_tokens;
			}
			else
			{
				to_write = ft_strdup(line);
			}
		}
		else
		{
			to_write = ft_strdup(line);
		}
		write(fd, to_write, ft_strlen(to_write));
		write(fd, "\n", 1);
		free(to_write);
		free(line);
	}
	close(fd);
	reset_signals_to_prompt();
	rl_event_hook = NULL;
	return (0);
}
