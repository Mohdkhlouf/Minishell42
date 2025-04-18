#include "../includes/minishell.h"

int	check_nl(char *new_line)
{
	int	i;

	i = 0;
	if (ft_strlen(new_line) <= 1)
		return (0);
	if (new_line[0] != '-')
		return (0);
	while (new_line[++i])
	{
		if (new_line[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(t_cmds *cmd, t_data *data)
{
	int	print_newline;
	int	i;

	(void)data;
	print_newline = 1;
	i = 1;
	if (cmd->cmd[i] && check_nl(cmd->cmd[i]))
	{
		print_newline = 0;
		i++;
	}
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i][0] == '\0')
		{
			i++;
			continue ;
		}
		ft_putstr_fd(cmd->cmd[i], 1);
		if (cmd->cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (print_newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
