/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:38:47 by akumari           #+#    #+#             */
/*   Updated: 2025/05/20 14:38:49 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	change_to_home_dir(t_data *data, char *home_dir, int *exit_code)
{
	char	*get_pwd;
	char	*copy_pwd;
	char	*copy_dir;

	if (chdir(home_dir) != 0)
		return (perror("minishell"), false);
	get_pwd = get_env_value("PWD", data);
	if (get_pwd)
	{
		copy_pwd = ft_strdup(get_pwd);
		if (!copy_pwd)
			return (false);
		update_env_list("OLDPWD", copy_pwd, data);
		free(copy_pwd);
	}
	else
	{
		copy_dir = ft_strdup(home_dir);
		if (!copy_dir)
			return (false);
		add_new_env_variable("PWD", copy_dir, data);
		free(copy_dir);
	}
	return (true);
}

char	*expand_path(t_data *data, char *path_value, int *exit_code)
{
	char	*expanded;
	char	*home;

	if (path_value[0] != '~')
		return (NULL);
	home = get_env_value("HOME", data);
	if (!home)
	{
		*exit_code = 1;
		print_error("cd: HOME not set");
		return (NULL);
	}
	expanded = ft_strjoin(home, path_value + 1);
	return (expanded);
}

bool	update_pwd_and_oldpwd(t_data *data, char *expanded, char *oldpwd,
		int *exit_code)
{
	char	*copy_oldpwd;
	char	*newpath;
	char	*copy_newpath;

	if (oldpwd)
	{
		copy_oldpwd = ft_strdup(oldpwd);
		if (!copy_oldpwd)
			return (false);
		update_env_list("OLDPWD", copy_oldpwd, data);
		free(copy_oldpwd);
	}
	newpath = getcwd(NULL, 0);
	if (!newpath)
	{
		check_on_fail_cd(exit_code, expanded);
		perror("cd: getcwd failed\n");
		return (false);
	}
	copy_newpath = ft_strdup(newpath);
	free(newpath);
	if (!copy_newpath)
		return (false);
	update_env_list("PWD", copy_newpath, data);
	return (free(copy_newpath), true);
}
