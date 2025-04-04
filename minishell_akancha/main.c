#include "main.h"

int main_loop(t_data *data)
{
	while (1)
	{
		data->cmd = readline("\033[0;35mminishell>\033[0m ");
		if (!data->cmd)
			return (0 * write(1, "\n", 1));
		if (cmds_process_loop(data))
			break;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	(void)argc;
	(void)argv;
	init_env(envp, &data);
	main_loop(&data);
	printf("\33[0;33mlogout\33[0m\n");
	return (0);
}
//  main
// print_env(data.env_lst);
//  data.path = get_path(data.env_lst);

// main loop
/*
signals are handled in the end
*/
// signal(SIGINT, handle_sigint);
// signal(SIGQUIT, handle_sigquit);
// if (ft_strncmp(data->cmd, "", 1))
// 	add_history(data->cmd);

// void print_env(t_var *head)
// {
// 	while (head)
// 	{
// 		printf("%s=%s\n", head->key, head->value);
// 		head = head->next;
// 	}
// }
