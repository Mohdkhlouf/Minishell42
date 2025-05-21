/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:47 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/21 02:37:08 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_builtin_handler(t_data *data, t_cmds *cmd, int *exit_code)
{
	dup2(cmd->saved_stdout, STDOUT_FILENO);
	dup2(cmd->saved_stdin, STDIN_FILENO);
	if (cmd->saved_stdout != -1)
		ft_close(&cmd->saved_stdout);
	if (cmd->saved_stdin != -1)
		ft_close(&cmd->saved_stdin);
	*exit_code = 1;
}

void	not_execute_builtin_handler(t_data *data, t_cmds *cmd, int *exit_code)
{
	dup2(cmd->saved_stdout, STDOUT_FILENO);
	dup2(cmd->saved_stdin, STDIN_FILENO);
	if (cmd->saved_stdout != -1)
		ft_close(&cmd->saved_stdout);
	if (cmd->saved_stdin != -1)
		ft_close(&cmd->saved_stdin);
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
	if (cmd->saved_stdout != -1)
		ft_close(&cmd->saved_stdout);
	if (cmd->saved_stdin != -1)
		ft_close(&cmd->saved_stdin);
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
	bool	sigquit_flag;

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
