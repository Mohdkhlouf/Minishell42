#include "../includes/minishell.h"

void	execute_builtin_handler(t_data *data, t_cmds *cmd, int *exit_code)
{
	dup2(cmd->saved_stdout, STDOUT_FILENO); // Restore original stdout
	dup2(cmd->saved_stdin, STDIN_FILENO);   // Restore original stdin
	close(cmd->saved_stdout);
	close(cmd->saved_stdin);
	*exit_code = 1;
}

void	not_execute_builtin_handler(t_data *data, t_cmds *cmd, int *exit_code)
{
	dup2(cmd->saved_stdout, STDOUT_FILENO); // Restore original stdout
	dup2(cmd->saved_stdin, STDIN_FILENO);   // Restore original stdin
	close(cmd->saved_stdout);
	close(cmd->saved_stdin);
}

bool	builtin_cmd(t_cmds *cmd, t_data *data, int *exit_code)
{
	cmd->saved_stdout = dup(STDOUT_FILENO);
	cmd->saved_stdin = dup(STDIN_FILENO);
	if (execute_redirections(data, cmd, exit_code))
	{
		if (!execute_builtin(data, cmd, exit_code))
			return (not_execute_builtin_handler(data, cmd, exit_code), false);
	}
	else
		return (execute_builtin_handler(data, cmd, exit_code), false);
	if (cmd->red_out_fd != -1)
		dup2(cmd->saved_stdout, STDOUT_FILENO);
	if (cmd->red_in_fd != -1)
		dup2(cmd->saved_stdin, STDIN_FILENO);
	close(cmd->saved_stdout);
	close(cmd->saved_stdin);
	return (true);
}

void	external_cmd(t_cmds *cmd, t_data *data, int *exit_code, pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		print_error("ERROR IN FORKING\n");
		exit(127);
	}
	if (*pid == 0)
	{
		if (!execute_redirections(data, cmd, exit_code))
		{
			cleanup_minishell(data);
			free(data);
			exit(1);
		}
		exec_cmd(cmd, data);
	}
}

void	handle_single_command(t_cmds *cmd, t_data *data, int *exit_code)
{
	pid_t	pid;
	int		status;
	int		signal_num;
	int		stop_signal;
	bool sigquit_flag;

	sigquit_flag = false;
	external_cmd(cmd, data, exit_code, &pid);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		*exit_code = WEXITSTATUS(status);
		data->exit_code = *exit_code;
	}
	else if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);
		if (signal_num == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (signal_num == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
		*exit_code = 128 + signal_num;
		data->exit_code = *exit_code;
	}
}

void	free_2d_cmd_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_cmd(t_cmds *cmd)
{
	free_2d_cmd_arr(cmd->cmd);
	free_2d_cmd_arr(cmd->reds);
}

void	not_execve_handler(t_cmds *cmd, t_data *data)
{
	perror("minishell");
	cleanup_minishell(data);
	data->exit_code = errno;
	exit(data->exit_code);
}

void	not_access_handler(t_cmds *cmd, t_data *data)
{
	ft_putstr_fd(cmd->cmd[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
	cleanup_minishell(data);
	exit(126); // Command found, but not executable
}

void	not_path_handler(t_cmds *cmd, t_data *data)
{
	/*Akancha null check here*/
	if (cmd && cmd->cmd && cmd->cmd[0])
	{
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	cleanup_minishell(data);
	free(data);
	exit(127);
}

void	path_with_slash_handler(t_cmds *cmd, t_data *data, char **path)
{
	struct stat	path_stat;

	*path = cmd->cmd[0];
	if (stat(*path, &path_stat) != 0)
	{
		perror("minishell");
		cleanup_minishell(data);
		data->exit_code = 127;
		exit(data->exit_code);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		cleanup_minishell(data);
		free(data);
		exit(126);
	}
}

void	path_as_command_handler(t_cmds *cmd, t_data *data, char **path)
{
	char	*temp_name;

	temp_name = NULL;
	if (cmd->cmd[0][0])
	{
		*path = find_path(data, cmd->cmd[0]);
		if (!*path)
		{
			temp_name = ft_strjoin("./", cmd->cmd[0]);
			if ((access(temp_name, F_OK) == 0))
			{
				*path = ft_strdup(temp_name);
				free(temp_name);
			}
			free(temp_name);
		}
	}
	else
	{
		cleanup_minishell(data);
		data->exit_code = 0;
		exit(0);
	}
}

/* main function to execute one command, i will make it execute the redirections
then do the command execution*/
void	exec_cmd(t_cmds *cmd, t_data *data)
{
	char	*path;

	path = NULL;
	set_child_signals();
	set_path(data);
	/*Akancha added for null check to prevent seg fault*/
	if (!cmd->cmd || !cmd->cmd[0])
	{
		not_path_handler(cmd, data);  // Or handle appropriately
		return;
	}
	if (ft_strchr(cmd->cmd[0], '/'))
		path_with_slash_handler(cmd, data, &path);
	else
		path_as_command_handler(cmd, data, &path);
	//printf("test path %s\n", path);
	if (!path)
		not_path_handler(cmd, data);
	if (access(path, X_OK) != 0)
		not_access_handler(cmd, data);
	if (execve(path, cmd->cmd, data->envp) == -1)
		not_execve_handler(cmd, data);
}
