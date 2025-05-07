#include "../includes/minishell.h"

// /*reset the signals from child process*/
// void set_default_signal_handlers(void)
// {
//     struct sigaction sa;

//     sa.sa_handler = SIG_DFL;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = 0;

//     sigaction(SIGINT, &sa, NULL);
//     sigaction(SIGQUIT, &sa, NULL);
// }

/* this function will start the fork to execute the cmd
i did the fork here.
then send the execution to child process*/

bool builtin_cmd(t_cmds *cmd, t_data *data, int *exit_code)
{
	int saved_stdout = dup(STDOUT_FILENO);
	int saved_stdin = dup(STDIN_FILENO);

	if (execute_redirections(data, cmd, exit_code))
	{
		if (execute_builtin(data, cmd, exit_code))
		{
			dup2(saved_stdout, STDOUT_FILENO); // Restore original stdout
			dup2(saved_stdin, STDIN_FILENO);   // Restore original stdin
			close(saved_stdout);
			close(saved_stdin);
			*exit_code = 1;
			return (false);
		}
	}
	else
	{
		dup2(saved_stdout, STDOUT_FILENO); // Restore original stdout
		dup2(saved_stdin, STDIN_FILENO);   // Restore original stdin
		close(saved_stdout);
		close(saved_stdin);
		*exit_code = 1;
		return (false);
	}

	if (cmd->red_out_fd != -1)
		dup2(saved_stdout, STDOUT_FILENO);
	if (cmd->red_in_fd != -1)
		dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	return (true);
}

void external_cmd(t_cmds *cmd, t_data *data, int *exit_code, pid_t *pid)
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
			exit(1);
		}

		exec_cmd(cmd, data);
	}
}

void handle_single_command(t_cmds *cmd, t_data *data, int *exit_code)
{
	pid_t pid;
	int status;
	int signal_num;
	int stop_signal;

	external_cmd(cmd, data, exit_code, &pid);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		*exit_code = WEXITSTATUS(status);
		// printf("Child process exited with code %d\n", *exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);
		// printf("Child process terminated by signal %d\n", signal_num);
	}
	else if (WIFSTOPPED(status))
	{
		// Child process stopped
		stop_signal = WSTOPSIG(status);
		// printf("Child process stopped by signal %d\n", stop_signal);
	}
}

void free_2d_cmd_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		ft_free(arr[i]);
		i++;
	}
	free(arr);
}

void free_cmd(t_cmds *cmd)
{
	free_2d_cmd_arr(cmd->cmd);
	free_2d_cmd_arr(cmd->reds);
}

/* main function to execute one command, i will make it execute the redirections
then do the command execution*/
void exec_cmd(t_cmds *cmd, t_data *data)
{
	char *path;
	struct stat path_stat;
	path = NULL;
	set_child_signals();
	if (ft_strchr(cmd->cmd[0], '/'))
	{
		path = cmd->cmd[0];
		if (stat(path, &path_stat) != 0)
		{
			perror("minishell");
			cleanup_minishell(data);
			data->exit_code = 127;
			exit(data->exit_code);
		}
		else if (S_ISDIR(path_stat.st_mode))
		{

			ft_putstr_fd("minishell: '", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			cleanup_minishell(data);
			free(data);
			exit(126);
		}
	}
	else
	{
		if (cmd->cmd[0][0])
			path = find_path(data, cmd->cmd[0]);
		else
		{
			cleanup_minishell(data);
			data->exit_code = 0;
			exit(0);
		}
	}
	if (!path)
	{
		// ft_putstr_fd("minishell: '", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		cleanup_minishell(data);
		free(data);
		exit(127);
	}
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		cleanup_minishell(data);
		exit(126); // Command found, but not executable
	}
	if (execve(path, cmd->cmd, data->envp) == -1)
	{
		perror("minishell");
		cleanup_minishell(data);
		data->exit_code = errno;
		exit(data->exit_code);
	}
}

// if (stat(path, &path_stat) != 0)
// {
// 	// perror("stat failed");
// 	return ;
// }
// if (S_ISDIR(path_stat.st_mode))
// 	data->exit_code = 126;
// else
// 	data->exit_code = 127;
// perror("minishell");

// while (data->env_lst)
// 	{
// 		size_t len = ft_strlen(path);
// 		while (len > 1 && path[len - 1] == '/')
// 		{
// 			path[len - 1] = '\0';
// 			len--;
// 		}
// 		if (ft_strcmp(get_env_value(data->env_lst->key, data), path))
// 		{

// 			ft_putstr_fd(cmd->cmd[0], 2);
// 			ft_putstr_fd(": Is a directory\n", 2);
// 			cleanup_minishell(data);
// 			exit(126);
// 		}
// 		data->env_lst = data->env_lst->next;
// 	}
