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
int builtin_cmd (t_cmds *cmd, t_data *data, int *exit_code)
{
	execute_redirections(data, cmd);
	if (is_builtin(cmd->cmd[0]) == 1)
	{
		if (execute_builtin(data, cmd, exit_code) == 0)
		{
			cleanup_minishell(data);
			exit(0);
		}
	}
}

int	external_cmd(t_cmds *cmd, t_data *data, int *exit_code)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error("ERROR IN FORKING\n");
		exit(127);
	}
	if (pid == 0)
	{
<<<<<<< HEAD
=======
		execute_redirections(data, cmd);
		if (is_builtin(cmd->cmd[0]) == 1)
		{
			if (execute_builtin(data, cmd, exit_code) == 0)
			{
				cleanup_minishell(data);
				exit(*exit_code);
			}
		}
>>>>>>> origin/main
		exec_cmd(cmd, data);
	}
	return (pid);
}

void	handle_single_command(t_cmds *cmd, t_data *data, int *exit_code)
{
	int	pid;
	int	status;
	int	signal_num;
	int	stop_signal;

	pid = 0;
	pid = external_cmd(cmd, data, exit_code);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		*exit_code = WEXITSTATUS(status);
		// printf("Child process exited with code %d\n", *exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);
		printf("Child process terminated by signal %d\n", signal_num);
	}
	else if (WIFSTOPPED(status))
	{
		// Child process stopped
		stop_signal = WSTOPSIG(status);
		printf("Child process stopped by signal %d\n", stop_signal);
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

/* main function to execute one command, i will make it execute the redirections
then do the command execution*/
void	exec_cmd(t_cmds *cmd, t_data *data)
{
	char	*path;

	path = NULL;
	set_child_signals();
	if (ft_strchr(cmd->cmd[0], '/'))
		path = cmd->cmd[0];
	else
		path = find_path(data, cmd->cmd[0]);
	if (!path)
	{
		// ft_putstr_fd("minishell: '", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		cleanup_minishell(data);
		exit(127);
	}
	if (execve(path, cmd->cmd, data->envp) == -1)
	{
		perror("minishell");
		cleanup_minishell(data);
		data->exit_code = 127;
		exit(127);
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