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
	int		fd;
	char	*line;
	t_token	tmp_token;
	char	*to_write;
	t_token	*original_tokens;
	struct sigaction	sa_old;


	//int fd_in_copy
	//fd_in_copy = dup(STDIN_FILENO)

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

// int get_heredoc_fd()
// {
// 	printf("I am here3.\n");
// 	return (open("HEREDOC_TEMP.txt", O_RDONLY));
// }

/*
--------------------Important one to use later---------------------------
static void	sigint_handler(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

	//Reset signal handler
	struct sigaction sa;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	signal interrupt
	if (g_heredoc_interrupted)
		return (-2);

	g_heredoc_interrupted = 0;
	// signal_handler_heredoc();
	bool no_expand;
	char *delimiter;
	int j;

	no_expand = false;
	if (input_delimiter, '\'') ||ft_strchr(input_delimiter, '"'))
		no_expand = true;

	delimiter = ft_calloc(1, ft_strlen(input_delimiter) + 1);
	j = 0;
	for (int i = 0; input_delimiter[i]; i++)
	{
		if (input_delimiter[i] != '\'' && input_delimiter[i] != '"')
			delimiter[j++] = input_delimiter[i];
	}
	dprintf(fd, "%s\n", to_write);
------------------------------------------------------------------------
	*/

// static char *expand_variables(char *line, t_data *data)
// {
// 	char *result = ft_calloc(1, 1);
// 	int i = 0;
// 	size_t new_len;

// 	while (line[i])
// 	{
// 		if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
// 		{
// 			i++;
// 			int start = i;
// 			while (ft_isalnum(line[i]) || line[i] == '_')
// 				i++;
// 			char *varname = ft_strndup(&line[start], i - start);
// 			char *value = get_env_value(varname, data);
// 			new_len = ft_strlen(result);
// 			if (value)
// 				new_len += ft_strlen(value);
// 			result = realloc(result, new_len + 1);
// 			if (value)
// 				ft_strcat(result, value);
// 			free(varname);
// 		}
// 		else
// 		{
// 			int len = ft_strlen(result);
// 			result = realloc(result, len + 2);
// 			result[len] = line[i];
// 			result[len + 1] = '\0';
// 			i++;
// 		}
// 	}
// 	return (result);
// }

// int handle_heredoc(char *input_delimiter, t_data *data, int expand)
// {
// 	int fd;
// 	char *line;
// 	char buff[1024];

// 	fd = open("HEREDOC_TEMP.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (-1);
// 	}

// 	while (1)
// 	{
// 		line = readline("heredoc> ");
// 		if (!line)
// 			break ;
// 		if (!input_delimiter)
// 		{
// 			printf("heredoc: null delimiter\n");
// 			free(line);
// 			break ;
// 		}
// 		if (ft_strcmp(line, input_delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		char *to_write = expand ? expand_variables(line,
				// data) : ft_strdup(line);
// 		ft_strncpy(buff, to_write, ft_strlen(to_write));
// 		buff[ft_strlen(to_write)] = '\n';
//     	buff[ft_strlen(to_write) + 1] = '\0';
// 		write(fd, buff, ft_strlen(buff));
// 		free(to_write);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
