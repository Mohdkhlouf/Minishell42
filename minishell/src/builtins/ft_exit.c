#include "../includes/minishell.h"

int ft_is_numeric(char *str)
{
	int i;

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

bool ft_exit(t_cmds *cmd, t_data *data, int *exit_code)
{
	(void)data;
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		*exit_code = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (false);
	}
	printf("exit\n");
	if (cmd->cmd[1])
	{
		if (!ft_is_numeric(cmd->cmd[1]))
		{
			ft_putstr_fd("minishell: exit: `", 2);
			ft_putstr_fd(cmd->cmd[1], 2);
			ft_putstr_fd("': numeric argument required\n", 2);
			*exit_code = 2;
		}
		else
			*exit_code = ft_atoi(cmd->cmd[1]);
	}
	exit(*exit_code);
}
// if (!cmd->cmd[1])
// 	printf("exit\n");
