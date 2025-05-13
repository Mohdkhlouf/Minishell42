#include "../includes/minishell.h"

int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

bool	ft_exit(t_cmds *cmd, t_data *data, int *exit_code)
{
	long long arg_value;

	if (cmd->cmd[1] && cmd->cmd[2])
	{
		*exit_code = 1;
		print_error("exit: too many arguments");
		return (false);
	}
	printf("exit\n");
	exit_shlvl(data);
	if (cmd->cmd[1])
	{
		if (!ft_is_numeric(cmd->cmd[1]))
		{
			minishell_error("exit", "numeric argument required", cmd->cmd[1]);
			*exit_code = 2;
		}
		else
		{
			arg_value = ft_atoi(cmd->cmd[1]);
			if (arg_value == LONG_MAX || arg_value == LONG_MIN)
            {
                minishell_error("exit", "numeric argument required", cmd->cmd[1]);
                *exit_code = 2;
            }
			else
				*exit_code = (int)arg_value;
		}
	}
	if (cmd->saved_stdin > 0)
		close(cmd->saved_stdin);
	if (cmd->saved_stdout > 0)
		close(cmd->saved_stdout);
	cleanup_minishell(data);
	free(data);
	exit(*exit_code);
}
