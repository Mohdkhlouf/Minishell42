#include "../includes/minishell.h"

void	execute_child(t_data *data, t_parsed_data *cmds_d, int i, int *prev_cmd,
		int *pipe_fd)
{
	if (*prev_cmd != -1)
	{
		dup2(*prev_cmd, STDIN_FILENO);
		close(*prev_cmd);
	}
	if (i < cmds_d->cmds_counter - 1)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	handle_command(&cmds_d->cmds[i], data);
	exit(0);
}

void	execute_parent(int *prev_cmd, int *pipe_fd, int i, int cmds_counter)
{
	if (*prev_cmd != -1)
		close(*prev_cmd);
	if (i < cmds_counter - 1)
	{
		close(pipe_fd[1]);
		*prev_cmd = pipe_fd[0];
	}
}

void	execute_pipes(t_data *data, t_parsed_data *cmds_d, int i, int *prev_cmd)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (i < cmds_d->cmds_counter && pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork(); // create a child process
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0) // child process
		execute_child(data, cmds_d, i, prev_cmd, pipe_fd);
	else
		execute_parent(prev_cmd, pipe_fd, i, cmds_d->cmds_counter);
}

void	handle_pipes(t_data *data, t_parsed_data *cmds_d)
{
	int	prev_cmd;
	int	i;
	int	j;

	prev_cmd = -1;
	j = 0;
	i = 0;
	while (i < cmds_d->cmds_counter)
	{
		execute_pipes(data, cmds_d, i, &prev_cmd);
		i++;
	}
	if (prev_cmd != -1)
		close(prev_cmd);
	while (j < cmds_d->cmds_counter)
	{
		wait(NULL);
		j++;
	}
}
