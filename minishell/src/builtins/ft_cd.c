/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:38:59 by akumari           #+#    #+#             */
/*   Updated: 2025/05/20 14:39:02 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	cd_with_no_param(t_data *data, int *exit_code)
{
	char	*home_dir;
	char	*get_pwd;

	*exit_code = 0;
	home_dir = get_env_value("HOME", data);
	if (!home_dir)
	{
		*exit_code = 1;
		return (ft_putstr_fd("cd: HOME not set\n", 2), false);
	}
	if (!change_to_home_dir(data, home_dir, exit_code))
		return (false);
	return (true);
}

static bool	cd_with_dash_param(t_data *data, int *exit_code)
{
	char	*pwd_path;
	char	*oldpwd_path;

	*exit_code = 0;
	pwd_path = ft_strdup(get_env_value("PWD", data));
	oldpwd_path = ft_strdup(get_env_value("OLDPWD", data));
	if (!pwd_path || !oldpwd_path)
	{
		ft_putstr_fd("cd: PWD or OLDPWD not set\n", 2);
		*exit_code = 1;
		return (free(pwd_path), free(oldpwd_path), false);
	}
	if (chdir(oldpwd_path) != 0)
	{
		perror("cd");
		*exit_code = 1;
		return (free(pwd_path), free(oldpwd_path), false);
	}
	update_env_list("PWD", oldpwd_path, data);
	update_env_list("OLDPWD", pwd_path, data);
	return (true);
}

static bool	cd_with_param(t_data *data, char *path_value, int *exit_code)
{
	char	*oldpwd;
	char	*expanded;

	*exit_code = 0;
	expanded = expand_path(data, path_value, exit_code);
	if (*exit_code == 1)
		return (false);
	if (expanded)
		path_value = expanded;
	if (chdir(path_value) != 0)
	{
		check_on_fail_cd(exit_code, expanded);
		if (errno == EACCES)
			minishell_error("cd", "Permission denied", path_value);
		else if (errno == ENOENT)
			minishell_error("cd", "No such file or directory", path_value);
		else
			minishell_error("cd", strerror(errno), path_value);
		return (free(expanded), false);
	}
	oldpwd = get_env_value("PWD", data);
	if (!update_pwd_and_oldpwd(data, expanded, oldpwd, exit_code))
		return (free(expanded), false);
	free(expanded);
	return (true);
}

bool	ft_cd(t_cmds *cmd, t_data *data, int *exit_code)
{
	char	*path_value;

	if (!cmd->cmd[1])
		return (cd_with_no_param(data, exit_code));
	if (cmd->cmd[0] && cmd->cmd[1] && !cmd->cmd[2])
	{
		path_value = cmd->cmd[1];
		if (ft_strncmp("-", path_value, ft_strlen(path_value)) == 0)
			return (cd_with_dash_param(data, exit_code));
		else
			return (cd_with_param(data, path_value, exit_code));
	}
	*exit_code = 1;
	if (cmd->cmd[2])
		return (print_error("cd : too many arguments"), false);
	return (false);
}
