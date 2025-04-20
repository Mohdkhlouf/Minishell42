#include "../includes/minishell.h"

int	builtin_with_redirect(t_cmds *cmds, t_data *data,
		int (*builtin_func)(t_cmds *, t_data *))
{
	int	result;
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO); // save terminal
	if (saved_stdout == -1)
	{
		print_error("dup failed");
		return (-1);
	}
	execute_redirections(data, cmds);
	result = builtin_func(cmds, data);
	dup2(saved_stdout, STDOUT_FILENO); // restore the terminal
	close(saved_stdout);// close temp fd to avoid leaks
	return (result);
}

int	is_builtin(char *cmd)
{
	const char	*builtins[] = {"cd", "exit", "echo", "pwd", "export", "unset",
		"env", NULL};
	int			i;

	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute_builtin(t_data *data, t_cmds *cmds)
{
	if (ft_strncmp(cmds->cmd[0], "echo", ft_strlen("echo")) == 0)
		return (builtin_with_redirect(cmds, data, ft_echo));
	else if (ft_strncmp(cmds->cmd[0], "pwd", ft_strlen("pwd")) == 0)
		return (builtin_with_redirect(cmds, data, ft_pwd));
	else if (ft_strncmp(cmds->cmd[0], "env", ft_strlen("env")) == 0)
		return (builtin_with_redirect(cmds, data, ft_env));
	else if (ft_strncmp(cmds->cmd[0], "cd", ft_strlen("cd")) == 0)
		return (builtin_with_redirect(cmds, data, ft_cd));
	else if (ft_strncmp(cmds->cmd[0], "export", ft_strlen("export")) == 0)
		return (builtin_with_redirect(cmds, data, ft_export));
	else if (ft_strncmp(cmds->cmd[0], "unset", ft_strlen("unset")) == 0)
		return (builtin_with_redirect(cmds, data, ft_unset));
	else if (ft_strncmp(cmds->cmd[0], "exit", ft_strlen("exit")) == 0)
		return (builtin_with_redirect(cmds, data, ft_exit));
	return (1);
}

void	execution(t_data *data, t_parsed_data *cmds_d)
{
	int	ret;
	int	i;

	i = 0;
	if (!data || !cmds_d)
		return ;
	if (cmds_d->cmds_counter == 0)
		return ;
	if (cmds_d->cmds_counter == 1)
	{
		if (is_builtin(cmds_d->cmds[i].cmd[0]) == 1)
		{
			ret = execute_builtin(data, &cmds_d->cmds[0]);
			if (ret == -1)
				printf("Command not found.\n");
			return ;
		}
		else
			handle_single_command(&cmds_d->cmds[0], data);
	}
	else
		handle_pipes(data, cmds_d);
	return ;
}
