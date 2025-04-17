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

int	ft_exit(t_cmds *cmd, t_data *data)
{
	int	exit_code;

	(void)data;
	exit_code = 0;
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else if (cmd->cmd[1])
	{
		if (!ft_is_numeric(cmd->cmd[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				cmd->cmd[1]);
			exit_code = 255;
		}
		else
		{
			printf("exit\n");
			exit_code = ft_atoi(cmd->cmd[1]);
		}
	}
	if (!cmd->cmd[1])
		printf("exit\n");
	exit(exit_code);
}
