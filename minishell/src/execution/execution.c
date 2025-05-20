#include "../includes/minishell.h"

void	set_data_exit_code_value(t_data *data, int *exit_code, int value)
{
	*exit_code = value;
	data->exit_code = *exit_code;
}

int	is_builtin(char *cmd)
{
	const char	*builtins[] = {"cd", "exit", "echo", "pwd", "export", "unset",
		"env", NULL};
	int			i;

	if (!cmd || !cmd[0])
		return (0);
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

bool	execute_builtin(t_data *data, t_cmds *cmds, int *exit_code)
{
	if (ft_strcmp(cmds->cmd[0], "echo") == 0)
		return (!ft_echo(cmds, data, exit_code));
	else if (ft_strcmp(cmds->cmd[0], "pwd") == 0)
		return (!ft_pwd(cmds, data, exit_code));
	else if (ft_strcmp(cmds->cmd[0], "env") == 0)
		return (!ft_env(cmds, data, exit_code));
	else if (ft_strcmp(cmds->cmd[0], "cd") == 0)
		return (!ft_cd(cmds, data, exit_code));
	else if (ft_strcmp(cmds->cmd[0], "export") == 0)
		return (!ft_export(cmds, data, exit_code));
	else if (ft_strcmp(cmds->cmd[0], "unset") == 0)
		return (!ft_unset(cmds, data, exit_code));
	else if (ft_strcmp(cmds->cmd[0], "exit") == 0)
		return (!ft_exit(cmds, data, exit_code));
	else
	{
		printf("%s: command not found\n", cmds->cmd[0]);
		return (set_data_exit_code_value(data, exit_code, 127), false);
	}
	return (true);
}

void	set_data_exit_code(t_data *data, int *exit_code)
{
	data->exit_code = *exit_code;
}

bool	execution(t_data *data, t_parsed_data *cmds_d)
{
	static int	exit_code = 0;

	if (!data || !cmds_d)
		return (set_data_exit_code_value(data, &exit_code, 0), false);
	if (cmds_d->cmds_counter == 0)
		return (set_data_exit_code_value(data, &exit_code, 0), false);
	if (!exec_heredoc(data, cmds_d))
		return (set_data_exit_code(data, &exit_code), false);
	if (cmds_d->cmds_counter == 1)
	{
		if (!cmds_d->cmds[0].cmd[0])
			return (set_data_exit_code_value(data, &exit_code, 0), false);
		if (cmds_d->cmds[0].cmd[0][0] == 0)
			return (true);
		if (is_builtin(cmds_d->cmds[0].cmd[0]))
		{
			if (!builtin_cmd(&cmds_d->cmds[0], data, &exit_code))
				return (set_data_exit_code(data, &exit_code), false);
		}
		else
			handle_single_command(&cmds_d->cmds[0], data, &exit_code);
	}
	else
		handle_pipes(data, data->cmds_d, &exit_code);
	return (set_data_exit_code(data, &exit_code), true);
}
