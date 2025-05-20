/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:21:55 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/21 00:53:00 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_parent(int *prev_cmd, t_data *data, int i, int cmds_counter)
{
	if (*prev_cmd != -1)
	{
		close(*prev_cmd);
		*prev_cmd = -1;
	}
	if (i < cmds_counter - 1)
	{
		if (data->pipe_fd[1] != -1)
			ft_close(&data->pipe_fd[1]);
		*prev_cmd = data->pipe_fd[0];
		printf("cmds->saved_stdout[%d] status %d\n", i, data->cmds_d->cmds->saved_stdout);
	}
	else
	{
		if (data->pipe_fd[0] != -1)
			ft_close(&data->pipe_fd[0]);
		if (data->pipe_fd[1] != -1)
			ft_close(&data->pipe_fd[1]);
		if (*prev_cmd != -1)
		{
			close(*prev_cmd);
			*prev_cmd = -1;
		}
		
		printf("data->pipe_fd[0] status %d\n", data->pipe_fd[0]);
		printf("data->pipe_fd[1] status %d\n", data->pipe_fd[1]);
		printf("cmds->red_in_fd status %d\n", data->cmds_d->cmds->red_in_fd);
		printf("cmds->red_in_fd status %d\n", data->cmds_d->cmds->red_in_fd);
		printf("cmds->saved_stdin status %d\n", data->cmds_d->cmds->saved_stdin);
		printf("cmds->saved_stdout status %d\n", data->cmds_d->cmds->saved_stdout);
		printf("cmds->saved_stdout[%d] status %d\n", i, data->cmds_d->cmds->saved_stdout);
	}
}

bool	execute_pipes(t_data *data, int i, int *prev_cmd, int *exit_code)
{
	/**/
	if (i > data->cmds_d->cmds_counter - 1)
	{
		if (data->pipe_fd[0] != -1)
			ft_close(&data->pipe_fd[0]);
		if (data->pipe_fd[1] != -1)
			ft_close(&data->pipe_fd[1]);
	}
	/**/
	if (i < data->cmds_d->cmds_counter - 1 && pipe(data->pipe_fd) == -1)
	{
		perror("pipe");
		return (false);
	}
	data->pid[i] = fork();
	if (data->pid[i] == -1)
	{
		perror("fork");
		return (false);
	}
	else if (data->pid[i] == 0)
		execute_child(data, i, prev_cmd, exit_code);
	else
		execute_parent(prev_cmd, data, i, data->cmds_d->cmds_counter);
	return (true);
}

void	wait_all(t_data *data, int *i, int *exit_code)
{
	int	signal_num;
	int	status;

	status = 0;
	signal_num = 0;
	if (waitpid(data->pid[*i], &status, 0) == -1)
		return ;
	if (WIFEXITED(status))
	{
		*exit_code = WEXITSTATUS(status);
		data->exit_code = *exit_code;
	}
	else if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);
		if (signal_num == SIGINT)
			data->sigterm_flag = true;
		else if (signal_num == SIGQUIT)
			data->sigquit_flag = true;
		*exit_code = 128 + signal_num;
		data->exit_code = *exit_code;
	}
}

bool	execute_pipes_loop(t_data *data, t_parsed_data *cmds_d, int prev_cmd,
		int *exit_code)
{
	int	i;
	int	old_prev_cmd;

	old_prev_cmd = -1;
	i = 0;
	while (i < cmds_d->cmds_counter)
	{
		if (!execute_pipes(data, i, &prev_cmd, exit_code))
			return (false);
		i++;
	}
	return (true);
}

bool	handle_pipes(t_data *data, t_parsed_data *cmds_d, int *exit_code)
{
	int	prev_cmd;
	int	i;

	prev_cmd = -1;
	i = 0;
	if (!allocate_pid(data, cmds_d))
		return (false);
	if (!execute_pipes_loop(data, cmds_d, prev_cmd, exit_code))
		return (false);
	if (prev_cmd != -1)
		close(prev_cmd);
	while (i < cmds_d->cmds_counter && data->pid[i] != -1)
	{
		wait_all(data, &i, exit_code);
		i++;
	}
	if (data->sigquit_flag)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
	if (data->sigterm_flag)
		write(STDOUT_FILENO, "\n", 1);
	if (data->pipe_fd[0] != -1)
		ft_close(&data->pipe_fd[0]);
	if (data->pipe_fd[1] != -1)
		ft_close(&data->pipe_fd[1]);
	return (free(data->pid), true);
}
