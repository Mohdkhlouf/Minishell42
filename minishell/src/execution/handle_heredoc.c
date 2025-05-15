#include "../includes/minishell.h"

static void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	g_signal_status = 1;
	write(STDOUT_FILENO, "\n", 1);
	// rl_done = 1; // Force readline() to return immediately
	//close(STDIN_FILENO); // alternative to rl_done
}

static void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0; // No SA_RESTART: readline must return NULL on Ctrl+C
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN; // Usually ignore Ctrl+\ during heredoc
	sigaction(SIGQUIT, &sa, NULL);
}

void	reset_signals_to_prompt(void)
{
	set_prompt_signals(); // Reapply prompt signal handlers
}

int	handle_heredoc(char *input_delimiter, t_data *data, int expand)
{
	int		fd;
	char	*line;
	t_token	tmp_token;
	char	*to_write;
	t_token	*original_tokens;

	//int fd_in_copy
	//fd_in_copy = dup(STDIN_FILENO)

	fd = open("HEREDOC_TEMP.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	set_heredoc_signals();
	while (1)
	{
		line = readline("heredoc> ");
		if (g_signal_status)
		{
			free(line);
			close(fd);
			unlink("HEREDOC_TEMP.txt");
			reset_signals_to_prompt();
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
