#include "../includes/minishell.h"

void print_error_2msgs(char *msg1, char *msg2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg2, 2);
	ft_putstr_fd("\n", 2);
}

void print_error(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void print_error_exit(char *msg, t_data *data, t_vars_data *var)
{
	if (msg)
		print_error(msg);
	if (data)
		free_data(data);
	if (var)
		free_var(var);
}

void minishell_error(char *context, char *message, char *errorfile)
{
	ft_putstr_fd("minishell: ", 2);
	if (context)
	{
		ft_putstr_fd(context, 2);
		ft_putstr_fd(": ", 2);
	}
	if (errorfile)
	{
		ft_putstr_fd(errorfile, 2);
		ft_putstr_fd(": ", 2);
	}

	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

void check_on_fail_cd(int *exit_code, char *expanded)
{
	*exit_code = 1;
	if (expanded)
		free(expanded);
}
