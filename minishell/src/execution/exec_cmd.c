/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:38 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/20 14:22:39 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	path_with_slash_handler2(t_cmds *cmd, t_data *data, char **path)
{
	struct stat	path_stat;

	if (stat(*path, &path_stat) != 0)
	{
		perror("minishell");
		cleanup_minishell(data);
		data->exit_code = 127;
		exit(data->exit_code);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: '", 2);
		ft_putstr_fd(*path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		cleanup_minishell(data);
		free(data);
		exit(126);
	}
}

void	command_stat_hhandler(t_cmds *cmd, t_data *data, char **path)
{
	struct stat	path_stat;

	if (stat(*path, &path_stat) != 0)
	{
		perror("minishell");
		cleanup_minishell(data);
		data->exit_code = 127;
		exit(data->exit_code);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(*path, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(*path);
		cleanup_minishell(data);
		free(data);
		exit(127);
	}
}

void	path_with_slash_handler(t_cmds *cmd, t_data *data, char **path)
{
	struct stat	path_stat;

	*path = cmd->cmd[0];
	if (stat(*path, &path_stat) != 0)
	{
		perror("minishell");
		data->exit_code = 127;
		cleanup_minishell(data);
		free(data);
		exit(127);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: '", 2);
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
		if (!*path && !data->parsed_path)
		{
			temp_name = ft_strjoin("./", cmd->cmd[0]);
			if ((access(temp_name, F_OK) == 0))
				*path = ft_strdup(temp_name);
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
	if (!cmd->cmd || !cmd->cmd[0] || cmd->cmd[0][0] == '\0')
	{
		cleanup_minishell(data);
		free(data);
		exit(0);
	}
	if (ft_strchr(cmd->cmd[0], '/'))
		path_with_slash_handler(cmd, data, &path);
	else
		path_as_command_handler(cmd, data, &path);
	if (!path)
		not_path_handler(cmd, data);
	if (access(path, X_OK) != 0)
		not_access_handler(cmd, data, path);
	command_stat_hhandler(cmd, data, &path);
	if (execve(path, cmd->cmd, data->envp) == -1)
		not_execve_handler(cmd, data, path);
}
