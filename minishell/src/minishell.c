#include "../includes/minishell.h"

volatile sig_atomic_t		g_exit_status = 0;

void	data_init(t_data *data)
{
	data->cline_parts = 0;
	data->input_line = NULL;
	data->tokens = NULL;
	data->end = 0;
	data->start = 0;
	data->in_token = false;
	data->tokens_conter = 0;
	data->quote_found = false;
	data->double_quote_found = false;
	data->quote_type = 0;
	data->file_seperator_found = false;
}

void	reading_loop(t_data *data, t_parsed_data *cmds_d)
{
	while (true)
	{
		data_init(data);
		data->input_line = readline("\033[0;35mminishell>\033[0m ");
		if (!data->input_line)
		{
			printf("Exit from EOF");
			free_matrix(data->parsed_path);
			free_env_list(data->env_lst);
			free(data->input_line);
			free(data->tokens);
			free(data);
			free(cmds_d);
			exit(0) ;
		}
		else if (ft_strcmp(data->input_line, "") != 0)
		{
			add_history(data->input_line);
			lexing(data);
			tokenizing(data);
			parsing(data, cmds_d);
			update_new_env(data);
			execution(data, cmds_d);
			free_matrix(data->envp);
			free_cmds_d(cmds_d);
			free_data(data);
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
	(void)envp;
	data = malloc(sizeof(t_data));
	cmds_d = malloc(sizeof(t_parsed_data));
	ft_memset(cmds_d, 0, sizeof(t_parsed_data));
	ft_memset(data, 0, sizeof(t_data));
	if (!data || !cmds_d)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	data_init(data);
	init_env(envp, data);
	start_signal();
	reading_loop(data, cmds_d);
	free(data);
	free(cmds_d);
	return (EXIT_SUCCESS);
}
