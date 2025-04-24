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
	path = find_path(data, cmd->cmd[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: '", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd("': command not found\n", 2);
		command_cleanup(data, data->cmds_d);
		free(data->cmds_d);
		free(data);
		exit(127);
	}
	if (execve(path, cmd->cmd, data->envp) == -1)
	{
		perror("minishell");
		free(path);
		free(cmd);
		data->exit_code = 127;
		exit(127);
	}
}

/* this function will start the fork to execute the cmd
i did the fork here.
then send the execution to child process*/
int	execute_cmd(t_cmds *cmd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error("ERROR IN FORKING\n");
		exit(127);
	}
	if (pid == 0)
		exec_cmd(cmd, data);
	return (pid);
}

void	handle_single_command(t_cmds *cmd, t_data *data, int *exit_code)
{
	int	ret;
	int	pid;
	int	status;
	int	signal_num;
	int	stop_signal;

	ret = 0;
	pid = 0;
	(void)data;
	if (!is_empty_cmd(cmd))
	{
		if (is_builtin(cmd->cmd[0]) == 1)
		{
			ret = execute_builtin(data, cmd, exit_code);
			if (ret == -1)
				print_error("Error.\n");
			printf("execute builtin \n");
		}
		else
		{
			execute_redirections(data, cmd);
			pid = execute_cmd(cmd, data);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				*exit_code = WEXITSTATUS(status);
				printf("Child process exited with code %d\n", *exit_code);
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
	}
	else
		handle_empty_cmd(cmd, data);
}

/*this function recieved a cmd struct, first i check if the command is empty
then if not, check if it is a built in, then will execute as built in.
if not, i use another function to start executing the external cmd*/
void	handle_command(t_cmds *cmd, t_data *data, int *exit_code)
{
	int ret;
	ret = 0;

	if (!is_empty_cmd(cmd))
	{
		if (is_builtin(cmd->cmd[0]) == 1)
		{
			/*function to execute builtin function the sent will be a command*/
			ret = execute_builtin(data, cmd, exit_code);
			if (ret == -1)
				print_error("Error.\n");
			printf("execute builtin \n");
		}
		else
		{
			execute_redirections(data, cmd);
			exec_cmd(cmd, data);
		}
	}
	else
		handle_empty_cmd(cmd, data);
}