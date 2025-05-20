/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:20:25 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/20 14:20:39 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*this function tests if the function is empty then print and return value.
it needs more later*/
bool	is_empty_cmd(t_cmds *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "") == 0)
	{
		return (true);
	}
	return (false);
}

void	not_execve_handler(t_cmds *cmd, t_data *data, char *path)
{
	perror("minishell");
	ft_free(path);
	cleanup_minishell(data);
	data->exit_code = errno;
	exit(data->exit_code);
}

void	not_access_handler(t_cmds *cmd, t_data *data, char *path)
{
	ft_putstr_fd(cmd->cmd[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
	if (!data->parsed_path && path)
		ft_free(path);
	cleanup_minishell(data);
	free(data);
	exit(126);
}

void	not_path_handler(t_cmds *cmd, t_data *data)
{
	ft_putstr_fd(cmd->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	cleanup_minishell(data);
	free(data);
	exit(127);
}

void	not_execute_builtin(t_data *data)
{
	cleanup_minishell(data);
	free(data);
	exit(0);
}
