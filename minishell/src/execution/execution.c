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

int	execute_builtin(t_data *data, t_cmds *cmds, int *exit_code)
{
	*exit_code = 0;
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

bool	execution(t_data *data, t_parsed_data *cmds_d)
{
	int	ret;
	static int exit_code = 0;
	int	i;

	i = 0;
	if (!data || !cmds_d)
		return (false);
	if (cmds_d->cmds_counter == 0)
		return (false);
	// if there is
	// 	handle_heredoc
	
	// if (check cmd  :only 1 and bulitin )
	// 	exuecute builtin in parent 
	// else 
	// {
	// 	handle pipe 
	// 	handle_redirection
	// 	{
	// 		if other RD 
	// 		if HD 
	// 			open fd, write the file content to write fd and cloe, return the read fd, 
	// 	}
	// }

	/* functionn to search and get input for all heredocs.
	the result of the last one wiill be stored in a file.*/
	
	while (cmds_d->cmds[0].reds[i])
	{
		if (ft_strcmp(cmds_d->cmds[0].reds[i], "<<") == 0)
		{
			if (handle_heredoc(cmds_d->cmds[0].reds[i + 1], data, 1) == 0)
			{
				int fd = get_heredoc_fd();
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
		}
		i++;
	}

	

	if (cmds_d->cmds_counter == 1)
	{
		if (is_builtin(cmds_d->cmds[i].cmd[0]) == 1)
		{
			ret = execute_builtin(data, &cmds_d->cmds[0], &exit_code);
			if (ret == -1)
				printf("Command not found.\n");
			// return (true);
		}
		else
			handle_single_command(&cmds_d->cmds[0], data, &exit_code);
	}
	else
		handle_pipes(data, cmds_d, &exit_code);

	data->exit_code = exit_code;
	return (true);
}
