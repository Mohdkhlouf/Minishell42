#include "../includes/minishell.h"

void	execute_child(t_data *data, t_parsed_data *cmds_d, int i, int *prev_cmd,
		int *exit_code)
{
	if (!execute_redirections(data, &cmds_d->cmds[i], exit_code))
	{
		// test solve this whoami | cat -e | cat -e > tmp/file
		// close(data->pipe_fd[0]);
		// close(data->pipe_fd[1]);
		cleanup_minishell(data);
		free(data);
		exit(1);
	}
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
	if (cmds_d->cmds[i].red_out_fd != -1)
	{
		dup2(cmds_d->cmds[i].red_out_fd, STDOUT_FILENO);
		close(cmds_d->cmds[i].red_out_fd);
	}
	else if (i < cmds_d->cmds_counter - 1)
	{
		close(data->pipe_fd[0]);
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
	}
	if (is_builtin(cmds_d->cmds[i].cmd[0]) == 1)
	{
		if (execute_builtin(data, &cmds_d->cmds[i], exit_code) == 0)
		{
			cleanup_minishell(data);
			free(data);
			exit(0);
		}
	}
	else
		exec_cmd(&cmds_d->cmds[i], data);
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
	data->pid[i] = fork(); // create a child process
	if (data->pid[i] == -1)
	{
		perror("fork");
		return (false);
	}
	else if (data->pid[i] == 0) // child process
		execute_child(data, cmds_d, i, prev_cmd, exit_code);
	else
		execute_parent(prev_cmd, data, i, cmds_d->cmds_counter);
	return (true);
}

void	wait_all(t_data *data, int *i, int *exit_code)
{
	int	signal_num;
	int status;

	status = 0;
	signal_num = 0;
	if (waitpid(data->pid[*i], &status, 0) == -1)
		return;
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

bool	handle_pipes(t_data *data, t_parsed_data *cmds_d, int *exit_code)
{
	int	prev_cmd;
	int	i;

	prev_cmd = -1;
	i = 0;
	if (!allocate_pid(data, cmds_d))
		return (false);
	while (i < cmds_d->cmds_counter)
	{
		if (!execute_pipes(data, cmds_d, i, &prev_cmd, exit_code))
			return (false);
		i++;
	}
	if (prev_cmd != -1)
		close(prev_cmd);
	i = 0;
	while (i < cmds_d->cmds_counter && data->pid[i] != -1)
	{
		wait_all(data, &i, exit_code);
		i++;
	}
	return (free(data->pid),true);
}
