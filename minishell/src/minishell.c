#include "../includes/minishell.h"

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

void	reading_loop(t_data *data, t_parsed_data	*cmds_d)
{		
	while (true)
	{
		data_init(data);
		data->input_line = readline("\033[0;35mminishell>\033[0m ");
		if(data->input_line == NULL)
		{
			printf("Exit");
			free(data->input_line);
			free(data);
			free(cmds_d);
			exit (EXIT_SUCCESS) ;
		}
		else if (ft_strcmp(data->input_line, "") != 0)
		{
			add_history(data->input_line);
			lexing(data);
			tokenizing(data);
			parsing(data, cmds_d);
			cmds_process_loop(data, cmds_d);
			free_data(data);
			free_cmds_d(cmds_d);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_parsed_data	*cmds_d;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	cmds_d = malloc(sizeof(t_parsed_data));
	if (!data || !cmds_d)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	data_init(data);
	init_env(envp, data);
	reading_loop(data, cmds_d);
	free_data(data);
	free_cmds_d(cmds_d);
	return (EXIT_SUCCESS);
}
