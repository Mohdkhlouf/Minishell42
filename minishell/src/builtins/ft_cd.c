#include "../includes/minishell.h"

static bool cd_with_no_param(t_data *data, int *exit_code)
{
	char *home_dir;
	char *get_pwd;

	*exit_code = 0;
	home_dir = get_env_value("HOME", data);
	if (!home_dir)
	{
		*exit_code = 1;
		return (ft_putstr_fd("cd: HOME not set\n", 2), false);
	}
	home_dir = ft_strdup(home_dir);
	if (!home_dir)
	{
		*exit_code = 1;
		return (ft_putstr_fd("cd: HOME not set\n", 2), false);
	}
	if (!change_to_home_dir(data, home_dir, exit_code))
		return (false);
	return (true);
}

static bool cd_with_dash_param(t_data *data, int *exit_code)
{
	char *pwd_path;
	char *oldpwd_path;

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

static bool cd_with_param(t_data *data, char *path_value, int *exit_code)
{
	char *newpath;
	char *oldpwd;
	char *expanded;

	*exit_code = 0;
	expanded = expand_path(data, path_value, exit_code);
	if (*exit_code == 1)
		return (false);
	if (expanded)
		path_value = expanded;
	if (chdir(path_value) != 0)
		return (check_on_fail_cd(exit_code, expanded), print_error("cd: No such file or directory"), false);
	oldpwd = get_env_value("PWD", data);
	if (oldpwd)
		update_env_list("OLDPWD", ft_strdup(oldpwd), data);
	// else
	// 	return (check_on_fail_cd(exit_code, expanded), minishell_error("cd", NULL, path_value), false);  // not err
	newpath = getcwd(NULL, 0);
	if (!newpath)
		return (check_on_fail_cd(exit_code, expanded), perror("cd: getcwd failed\n"), false);
	update_env_list("PWD", ft_strdup(newpath), data);
	free(newpath);
	if (expanded)
		free(expanded);
	return (true);
}

bool ft_cd(t_cmds *cmd, t_data *data, int *exit_code)
{
	char *path_value;

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

// static bool	cd_with_no_param(t_data *data, int *exit_code)
// {
// 	char	*home_dir;
// 	char	*temp;
// 	char *oldpwd;

// 	temp = NULL;
// 	*exit_code = 0;
// 	home_dir = ft_strdup(get_env_value("HOME", data));
// 	if (!home_dir)
// 	{
// 		print_error("I am in homedir");
// 		*exit_code = 1;
// 		return (ft_putstr_fd("cd: HOME not set\n", 2), false);
// 	}
// 	if (chdir(home_dir) != 0)
// 	{
// 		print_error("I am in chdir");
// 		*exit_code = 1;
// 		return (perror("minishell"), free(home_dir), false);
// 	}
// 	oldpwd = ft_strdup("OLDPWD");
// 	if(oldpwd)
// 	{
// 		print_error("I am in oldpwd");
// 		update_env_list(oldpwd, ft_strdup(get_env_value("PWD", data)), data);
// 	}
// 	if(oldpwd)
// 		free(oldpwd);
// 	temp = ft_strdup("PWD");
// 	if (temp)
// 	{
// 		print_error("I am in temp");
// 		update_env_list(temp, home_dir, data);
// 	}
// 	if(temp)
// 		free(temp);
// 	return (true);
// }