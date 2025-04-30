#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

void	data_init(t_data *data, t_parsed_data *cmds_d)
{
	// data->cmds_d = cmds_d;
	// data->cline_parts = 0;
	// data->input_line = NULL;
	// data->tokens = NULL;
	// data->end = 0;
	// data->start = 0;
	// data->in_token = false;
	// data->tokens_conter = 0;
	// data->quote_found = false;
	// data->double_quote_found = false;
	// data->quote_type = 0;
	// data->file_seperator_found = false;
	// data->first_quote_type = 0;

	// Initialize t_parsed_data
	cmds_d->cmds = NULL;
	cmds_d->cmds_counter = 0;
	cmds_d->pipes_counter = 0;
	cmds_d->cmds_ctr = 0;
	cmds_d->red_ctr = 0;
	cmds_d->token_ctr = 0;

	// Initialize t_data
	data->cmds_d = cmds_d;
	data->tokens = NULL;
	data->end = 0;
	data->start = 0;
	data->pid = 0;
	data->in_token = false;
	data->quote_found = false;
	data->double_quote_found = false;
	data->first_quote_type = 0;
	data->file_seperator_found = false;
	data->variable_sign_found = false;
	data->input_line = NULL;
	data->quote_type = 0;
	data->pwd = NULL;
	data->envp = NULL;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->exit_code = 0;
	data->cline_parts = 0;
	data->tokens_conter = 0;
}

void	command_cleanup(t_data *data, t_parsed_data *cmds_d)
{
	free_matrix(data->envp);
	// free_2arr_general(data->parsed_path);
	// free_env_list(data->env_lst);
	free_cmds_d(cmds_d);
	free_data(data);
}

bool	pre_validation(t_data *data)
{
	int	len;

	len = 0;
	len = ft_strlen(data->input_line);
	// test the last letter in the line
	if (data->input_line[len - 1] == '<' || data->input_line[len - 1] == '>'
		|| data->input_line[len - 1] == '|')
	{
		print_error("syntax error near unexpected token `|'");
		data->exit_code = 2;
		return (false);
	}

	return (true);
}
void	reading_loop(t_data *data, t_parsed_data *cmds_d)
{
	while (true)
	{
		data_init(data, cmds_d);
		data->input_line = readline("\033[0;35mminishell>\033[0m ");
		if (!data->input_line)
		{
			free_matrix(data->parsed_path);
			free_env_list(data->env_lst);
			ft_free(data->input_line);
			free(data->tokens);
			free(data);
			free(cmds_d);
			exit(0);
		}
		else if (ft_strcmp(data->input_line, "") != 0)
		{
			add_history(data->input_line);
			if (!pre_validation(data) || !lexing(data) || !tokenizing(data)
				|| !parsing(data, cmds_d) || !update_new_env(data)
				|| !execution(data, cmds_d))
			{
				command_cleanup(data, cmds_d);
				continue ;
			}
			command_cleanup(data, cmds_d);
		}
		free(data->input_line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data			*data;
	t_parsed_data	*cmds_d;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	cmds_d = ft_calloc(1, sizeof(t_parsed_data));
	if (!data || !cmds_d)
	{
		free(data);
		free(cmds_d);
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	data_init(data, cmds_d);
	init_env(envp, data);
	set_prompt_signals();
	reading_loop(data, cmds_d);
	free(data);
	free(cmds_d);
	printf("END OF MAIN FILE REACHED\n");
	return (g_signal_status);
}
