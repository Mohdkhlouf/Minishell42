#include "../includes/minishell.h"

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

void	when_g_signal_status(int fd, char *line, char *input_delimiter)
{
	free(line);
	free(input_delimiter);
	close(fd);
	unlink("HEREDOC_TEMP.txt");
	reset_signals_to_prompt();
	rl_event_hook = NULL;
}

void	case_expand(t_data *data, char **to_write, char *line)
{
	t_token	tmp_token;
	t_token	*original_tokens;

	if (ft_strchr(line, '$'))
	{
		tmp_token.data = ft_strdup(line);
		tmp_token.type = TOK_STRING;
		original_tokens = data->tokens;
		data->tokens = &tmp_token;
		var_handler2(data, 0);
		*to_write = ft_strdup(tmp_token.data);
		free(tmp_token.data);
		data->tokens = original_tokens;
	}
	else
	{
		*to_write = ft_strdup(line);
	}
}

void	closing_heredoc(int fd)
{
	close(fd);
	reset_signals_to_prompt();
	rl_event_hook = NULL;
}

bool	open_file(int *fd)
{
	struct sigaction	sa_old;

	*fd = open("HEREDOC_TEMP.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*fd < 0)
		return (perror("open"), false);
	set_heredoc_signals(&sa_old);
	rl_event_hook = heredoc_event_hook;
	return (true);
}

int	handle_heredoc(char *input_delimiter, t_data *data, int expand)
{
	int	fd;

	if (!open_file(&fd))
		return (-1);
	while (1)
	{
		data->here_line = readline("heredoc> ");
		if (g_signal_status)
			return (when_g_signal_status(fd, data->here_line, input_delimiter),
				1);
		if (!data->here_line)
			break ;
		if (!input_delimiter)
			return (free(data->here_line), printf("null delimiter\n"),
				closing_heredoc(fd), 0);
		if (ft_strcmp(data->here_line, input_delimiter) == 0)
			return (free(data->here_line), closing_heredoc(fd), 0);
		if (expand == 1)
			case_expand(data, &data->here_to_write, data->here_line);
		else
			data->here_to_write = ft_strdup(data->here_line);
		write_free_heredoc(fd, data->here_to_write, data->here_line);
	}
	return (closing_heredoc(fd), 0);
}
