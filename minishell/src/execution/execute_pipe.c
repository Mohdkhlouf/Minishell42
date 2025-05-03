#include "../includes/minishell.h"

void	execute_child(t_data *data, t_parsed_data *cmds_d, int i, int *prev_cmd,
		int *pipe_fd, int *exit_code)
{
	// Redirection handling
	if (!execute_redirections(data, &cmds_d->cmds[i]))
		return ;
	// Handle standard input redirection
	if (cmds_d->cmds[i].red_in_fd != -1)
	{
		dup2(cmds_d->cmds[i].red_in_fd, STDIN_FILENO);
		close(cmds_d->cmds[i].red_in_fd);
	}
	else if (*prev_cmd != -1)
	{
		dup2(*prev_cmd, STDIN_FILENO);
		close(*prev_cmd);
	}
	// Handle standard output redirection
	if (cmds_d->cmds[i].red_out_fd != -1)
	{
		dup2(cmds_d->cmds[i].red_out_fd, STDOUT_FILENO);
		close(cmds_d->cmds[i].red_out_fd);
	}
	// If it's not the last command in the pipeline,we connect it to the next command
	else if (i < cmds_d->cmds_counter - 1)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	// Execute the command
	handle_command(&cmds_d->cmds[i], data, exit_code);
}

void	execute_parent(int *prev_cmd, t_data *data, int i, int cmds_counter)
{
		// Close the previous pipe if it exists
		if (*prev_cmd != -1)
		{
			close(*prev_cmd);
		}
	
		// If not the last command, set up for the next one
		if (i < cmds_counter - 1)
		{
			close(data->pipe_fd[1]);
			*prev_cmd = data->pipe_fd[0];
		}
		else
		{
			// Close both pipe ends when it's the last command
			close(data->pipe_fd[0]);
			close(data->pipe_fd[1]);
			*prev_cmd = -1;
		}
}

bool	allocate_pid(t_data *data, t_parsed_data *cmds_d)
{
	data->pid = ft_calloc(cmds_d->cmds_counter, sizeof(pid_t));
	if (!data->pid)
	{
		return (false);
	}
	return (true);
}

bool	execute_pipes(t_data *data, t_parsed_data *cmds_d, int i, int *prev_cmd,
		int *exit_code)
{
	if (i < cmds_d->cmds_counter && pipe(data->pipe_fd) == -1)
	{
		perror("pipe");
		return (false);
	}
	if (!allocate_pid(data, cmds_d))
		return (false);
	data->pid[i] = fork(); // create a child process
	if (data->pid[i] == -1)
	{
		perror("fork");
		return (false);
	}
	else if (data->pid[i] == 0) // child process
		execute_child(data, cmds_d, i, prev_cmd, data->pipe_fd, exit_code);
	else
		execute_parent(prev_cmd, data, i, cmds_d->cmds_counter);
	return (true);
}

bool	handle_pipes(t_data *data, t_parsed_data *cmds_d, int *exit_code)
{
	int	prev_cmd;
	int	status;
	int	i;
	int	signal_num;
	int	stop_signal;

	prev_cmd = -1;
	i = 0;
	status = 0;
	while (i < cmds_d->cmds_counter)
	{
		if (!execute_pipes(data, cmds_d, i, &prev_cmd, exit_code))
			return (false);
		i++;
	}
	if (prev_cmd != -1)
	{
		close(prev_cmd);
	}
	i = 0;
	while (i < cmds_d->cmds_counter && data->pid[i] != -1)
	{
		waitpid(data->pid[i], &status, 0);
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
		i++;
	}
	free(data->pid);
	data->pid = NULL;
	return (true);
}
