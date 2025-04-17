#include "../includes/minishell.h"

void	print_error(char *msg)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("minishell:%s", msg);
}

void	print_error_exit(char *msg, t_data *data, t_vars_data *var)
{
	if (msg)
		print_error(msg);
	if (data)
		free_data(data);
	if (var)
		free_var(var);
}
