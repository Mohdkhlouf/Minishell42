#include "../includes/minishell.h"

int is_builtin(char *cmd)
{
	const char *builtins[] = {"cd", "exit", "echo", "pwd", "export", "unset",
							  "env", NULL};
	int i;

	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

bool execute_builtin(t_data *data, t_cmds *cmds, int *exit_code)
{
	if (ft_strncmp(cmds->cmd[0], "echo", ft_strlen("echo")) == 0)
		return (!ft_echo(cmds, data, exit_code));
	else if (ft_strncmp(cmds->cmd[0], "pwd", ft_strlen("pwd")) == 0)
		return (!ft_pwd(cmds, data, exit_code));
	else if (ft_strncmp(cmds->cmd[0], "env", ft_strlen("env")) == 0)
		return (!ft_env(cmds, data, exit_code));
	else if (ft_strncmp(cmds->cmd[0], "cd", ft_strlen("cd")) == 0)
		return (!ft_cd(cmds, data, exit_code));
	else if (ft_strncmp(cmds->cmd[0], "export", ft_strlen("export")) == 0)
		return (!ft_export(cmds, data, exit_code));
	else if (ft_strncmp(cmds->cmd[0], "unset", ft_strlen("unset")) == 0)
		return (!ft_unset(cmds, data, exit_code));
	else if (ft_strncmp(cmds->cmd[0], "exit", ft_strlen("exit")) == 0)
		return (!ft_exit(cmds, data, exit_code));
	return (true);
}

void set_data_exit_code(t_data *data, int *exit_code)
{
	data->exit_code = *exit_code;
}

bool execution(t_data *data, t_parsed_data *cmds_d)
{
	static int exit_code = 0;

	if (!data || !cmds_d)
		return (false);
	if (cmds_d->cmds_counter == 0)
		return (false);

	if (!exec_heredoc(data, cmds_d))
		return (false);
	if (cmds_d->cmds_counter == 1)
	{
		if (!cmds_d->cmds[0].cmd[0])
			return (false);
		// return(print_error("command is not found"),false);
		if (is_builtin(cmds_d->cmds[0].cmd[0]))
		{
			if (!builtin_cmd(&cmds_d->cmds[0], data, &exit_code))
				return (set_data_exit_code(data, &exit_code), false);
		}
		else
			handle_single_command(&cmds_d->cmds[0], data, &exit_code);
	}
	else
		handle_pipes(data, cmds_d, &exit_code);

	data->exit_code = exit_code;
	return (true);
}
