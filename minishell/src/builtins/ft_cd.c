#include "../includes/minishell.h"

// TODO return value

static int	cd_with_no_param(t_data *data)
{
	char	*home_dir;

	home_dir = ft_strdup(get_env_value("HOME", data));
	if (!home_dir)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (-1);
	}
	if (chdir(home_dir) != 0)
	{
		perror("minishell");
		free(home_dir);
		return (-1);
	}
	update_env_list(ft_strdup("OLDPWD"), ft_strdup(get_env_value("PWD", data)),
		data);
	update_env_list(ft_strdup("PWD"), home_dir, data);
	return (0);
}

static int	cd_with_dash_param(t_data *data)
{
	char	*pwd_path;
	char	*oldpwd_path;

	pwd_path = ft_strdup(get_env_value("PWD", data));
	oldpwd_path = ft_strdup(get_env_value("OLDPWD", data));
	if (!pwd_path || !oldpwd_path)
	{
		ft_putstr_fd("cd: PWD or OLDPWD not set\n", 2);
		free(pwd_path);
		free(oldpwd_path);
		return (-1);
	}
	if (chdir(oldpwd_path) != 0)
	{
		perror("cd");
		free(pwd_path);
		free(oldpwd_path);
		return (-1);
	}
	update_env_list(ft_strdup("PWD"), oldpwd_path, data);
	update_env_list(ft_strdup("OLDPWD"), pwd_path, data);
	return (0);
}

static int	cd_with_param(t_data *data, char *path_value, int *exit_code)
{
	char	*newpath;

	if (chdir(path_value) != 0)
	{
		*exit_code = 1;
		print_error("cd: No such file or directory");
		return (1);
	}
	update_env_list(ft_strdup("OLDPWD"), ft_strdup(get_env_value("PWD", data)),
		data);
	newpath = getcwd(NULL, 0);
	if (!newpath)
	{
		perror("cd: getcwd failed\n");
		*exit_code = 1;
		return (-1);
	}
	update_env_list(ft_strdup("PWD"), ft_strdup(newpath), data);
	free(newpath);
	*exit_code = 0;
	return (0);
}

int	ft_cd(t_cmds *cmd, t_data *data, int *exit_code)
{
	char	*path_value;

	if (!cmd->cmd[1])
		return (cd_with_no_param(data));
	else if (cmd->cmd[0] && cmd->cmd[1] && !cmd->cmd[2])
	{
		path_value = cmd->cmd[1];
		if (ft_strncmp("-", path_value, ft_strlen(path_value)) == 0)
			return (cd_with_dash_param(data));
		else
			return (cd_with_param(data, path_value, exit_code));
		*exit_code = 1;
		return (1);
	}
	else if(cmd->cmd[2])
	{
		print_error("cd : too many arguments");
		*exit_code = 1;
		return (1);
	}
	else
	{
		if (chdir(cmd->cmd[1]) != 0)
		{	
			perror("minishell");
			/* we have to add exit code in this case*/
			*exit_code = 1;
			return (1);
		}
	}
	// *exit_code = 0;
	return (0);
}
