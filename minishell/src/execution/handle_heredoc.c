#include "../includes/minishell.h"

static char *expand_variables(char *line, t_data *data)
{
	char *result = ft_calloc(1, 1);
	int i = 0;
	size_t new_len;

	while (line[i])
	{
		if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
		{
			i++;
			int start = i;
			while (ft_isalnum(line[i]) || line[i] == '_')
				i++;
			char *varname = ft_strndup(&line[start], i - start);
			char *value = get_env_value(varname, data);
			new_len = ft_strlen(result);
			if (value)
				new_len += ft_strlen(value);
			result = realloc(result, new_len + 1);
			if (value)
				ft_strcat(result, value);
			free(varname);
		}
		else
		{
			int len = ft_strlen(result);
			result = realloc(result, len + 2);
			result[len] = line[i];
			result[len + 1] = '\0';
			i++;
		}
	}
	return (result);
}

int handle_heredoc(char *input_delimiter, t_data *data, int expand)
{
	int fd;
	char *line;
	char buff[1024];

	fd = open("HEREDOC_TEMP.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break;
		if (!input_delimiter)
		{
			printf("heredoc: null delimiter\n");
			free(line);
			break;
		}
		if (ft_strcmp(line, input_delimiter) == 0)
		{
			free(line);
			break;
		}
		char *to_write = expand ? expand_variables(line, data) : ft_strdup(line);
		ft_strncpy(buff, to_write, ft_strlen(to_write));
		buff[ft_strlen(to_write)] = '\n';
    	buff[ft_strlen(to_write) + 1] = '\0';
		write(fd, buff, ft_strlen(buff));
		free(to_write);
		free(line);
	}
	close(fd);
	return (0);
}

// int get_heredoc_fd()
// {
// 	printf("I am here3.\n");
// 	return open("HEREDOC_TEMP.txt", O_RDONLY);
// }

/* 
--------------------Important one to use later---------------------------
static void sigint_handler(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void signal_handler_heredoc()
{
	struct sigaction sa;
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



// char *expand_var(char *line, size_t *i, t_data *data)
// {
// 	size_t len;
// 	size_t start;
// 	size_t end;

// 	start = *i + 1;
// 	end = start;
// 	while ((line[end] >= 'a' && line[end] <= 'z') ||
// 		   (line[end] >= 'A' && line[end] <= 'Z') ||
// 		   line[end] == '_')
// 	{
// 		end++;
// 	}
// 	len = end - start;
// 	char *var_name = ft_strndup(line + start, len);
// 	char *var_value = get_env_value(var_name, data);
// 	free(var_name);
// 	if (var_value)
// 	{
// 		*i = end - 1;
// 		return ft_strdup(var_value);
// 	}
// 	return (strdup(""));
// }

// static char *expand_variables(char *line, t_data *data, int is_quote_heredoc)
// {
// 	size_t i;
// 	size_t len;
// 	char *expanded_line;
// 	size_t j;
// 	char *expanded_var;
// 	int in_single_quote;
// 	int in_double_quote;
// 	size_t k;

// 	i = 0;
// 	j = 0;
// 	in_single_quote = 0;
// 	in_double_quote = 0;
// 	len = ft_strlen(line);
// 	expanded_line = malloc(len + 1);
// 	if (!expanded_line)
// 	{
// 		return NULL;
// 	}
// 	while (i < len)
// 	{
// 		if (line[i] == '\'' && !in_double_quote && !is_quote_heredoc)
// 		{
// 			in_single_quote = !in_single_quote;
// 			expanded_line[j++] = line[i++];
// 		}
// 		else if (line[i] == '"' && !in_single_quote)
// 		{
// 			in_double_quote = !in_double_quote;
// 			expanded_line[j++] = line[i++];
// 		}
// 		else if (line[i] == '$' && !in_single_quote && !is_quote_heredoc)
// 		{
// 			expanded_var = expand_var(line, &i, data);
// 			if (expanded_var)
// 			{
// 				k = 0;
// 				while (expanded_var[k])
// 				{
// 					expanded_line[j++] = expanded_var[k++];
// 				}
// 				free(expanded_var);
// 			}
// 		}
// 		else
// 		{
// 			expanded_line[j++] = line[i++];
// 		}
// 	}

// 	expanded_line[j] = '\0';
// 	return (expanded_line);
// }

// void set_heredoc_signals(struct sigaction *sa_old)
// {
// 	struct sigaction new_sa;

// 	ft_memset(&new_sa, 0, sizeof(new_sa));
// 	new_sa.sa_handler = handle_heredoc_signals;
// 	new_sa.sa_flags = SA_RESTART;
// 	sigemptyset(&new_sa.sa_mask);
// 	if (sigaction(SIGINT, &new_sa, sa_old) == -1)
// 		return;
// }

// static void restore_signals(struct sigaction *old_sa)
// {
// 	if (old_sa)
// 		sigaction(SIGINT, old_sa, NULL);
// 	rl_catch_signals = 1;
// 	rl_event_hook = NULL;
// }

// static void heredoc_warning(char *delimeter)
// {
// 	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
// 	ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
// 	ft_putstr_fd(delimeter, STDERR_FILENO);
// 	ft_putendl_fd("')", STDERR_FILENO);
// }

// static int heredoc_input(char **joined_lines, char *delimeter)
// {
// 	char *line;

// 	line = readline("> ");
// 	if (!line)
// 	{
// 		heredoc_warning(delimeter);
// 		return (1);
// 	}
// 	if (ft_strcmp(line, delimeter) == 0)
// 	{
// 		free(line);
// 		return (1);
// 	}
// 	if (heredoc_join(joined_lines, line))
// 		return (1);
// 	return (0);
// }

// void get_hd_lines(t_parsed_data *cmds_d, char *delimiter)
// {
// 	struct sigaction sa_old;
// 	char *joined_lines;

// 	if (!cmds_d)
// 		return (1);
// 	set_heredoc_signals(&sa_old);
// 	rl_event_hook = heredoc_event_hook;
// 	rl_catch_signals = 0;
// 	joined_lines = ft_strdup("");
// 	if (!joined_lines)
// 		return (1);
// 	while (!g_store_sigint)
// 	{
// 		if (heredoc_input(&joined_lines, rd_list[i].file_deli))
// 			break;
// 	}
// 	restore_signals(&sa_old);
// 	if (!g_store_sigint)
// 		rd_list[i].hd_lines = expand_heredoc(mshell, joined_lines, is_quote);
// 	else
// 		free(joined_lines);
// 	return (0);
// }

// int heredoc_handle(t_parsed_data *cmds_d)
// {
// 	int i;
// 	int j;
// 	int rd_len;

// 	i = 0;


// 	// while (mshell->cmds && i < mshell->count_cmds)
// 	// {
// 	// 	j = 0;
// 	// 	rd_len = get_rd_list_len(mshell->cmds[i].token);
// 	// 	while (j < rd_len)
// 	// 	{
// 	// 		if (mshell->cmds[i].redirects[j].rd_type == RD_HEREDOC)
// 	// 		{
// 	// 			*status = get_hd_lines(mshell, mshell->cmds[i].redirects, j,
// 	// 					mshell->cmds[i].is_hd_quote);
// 	// 		}
// 	// 		j++;
// 	// 	}
// 	// 	i++;
// 	// }
// 	return (EXIT_FAILURE);
// }
