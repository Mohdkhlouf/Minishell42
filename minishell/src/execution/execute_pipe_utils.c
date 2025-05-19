#include "../includes/minishell.h"

void	not_execute_redirections_handler(t_data *data)
{
	cleanup_minishell(data);
	free(data);
	exit(1);
}

void	dup_red_in_close(t_parsed_data *cmds_d, int i)
{
	dup2(cmds_d->cmds[i].red_in_fd, STDIN_FILENO);
	close(cmds_d->cmds[i].red_in_fd);
}

void	dup_red_out_close(t_parsed_data *cmds_d, int i)
{
	dup2(cmds_d->cmds[i].red_out_fd, STDOUT_FILENO);
	close(cmds_d->cmds[i].red_out_fd);
}

void	pipe_fd_close_dup(t_data *data)
{
	close(data->pipe_fd[0]);
	dup2(data->pipe_fd[1], STDOUT_FILENO);
	close(data->pipe_fd[1]);
}

void	execute_child(t_data *data,int i, int *prev_cmd,
		int *exit_code)
{
	if (!execute_redirections(data, &data->cmds_d->cmds[i], exit_code))
		not_execute_redirections_handler(data);
	if (data->cmds_d->cmds[i].red_in_fd != -1)
		dup_red_in_close(data->cmds_d, i);
	else if (*prev_cmd != -1)
	{
		dup2(*prev_cmd, STDIN_FILENO);
		close(*prev_cmd);
	}
	if (data->cmds_d->cmds[i].red_out_fd != -1)
		dup_red_out_close(data->cmds_d, i);
	else if (i < data->cmds_d->cmds_counter - 1)
		pipe_fd_close_dup(data);
	if (is_builtin(data->cmds_d->cmds[i].cmd[0]) == 1)
	{
		if (execute_builtin(data, &data->cmds_d->cmds[i], exit_code) == 0)
			not_execute_builtin(data);
	}
	else
		exec_cmd(&data->cmds_d->cmds[i], data);
}
