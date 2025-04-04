



#include "../includes/minishell.h"
// TODO return value

void cd_with_no_param(t_data *data)
{
	char *home_dir;
	home_dir = ft_strdup(get_env_value("HOME", data));
	if (!home_dir)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return;
	}
	if (chdir(home_dir) != 0)
	{
		perror("minishell");
		return;
	}
	add_env_list(ft_strdup("OLDPWD"), ft_strdup(get_env_value("PWD", data)), data);
	add_env_list(ft_strdup("PWD"), home_dir, data);
}

void cd_with_dash_param(t_data *data)
{
	char *pwd_path;
	char *oldpwd_path;
	pwd_path = ft_strdup(get_env_value("PWD", data));
	oldpwd_path = ft_strdup(get_env_value("OLDPWD", data));
	if (!pwd_path || !oldpwd_path)
	{
		ft_putstr_fd("cd: PWD or OLDPWD not set\n", 2);
		return;
	}
	if (chdir(oldpwd_path) != 0)
	{
		perror("cd");
		return;
	}
	add_env_list(ft_strdup("PWD"), oldpwd_path, data);
	add_env_list(ft_strdup("OLDPWD"), pwd_path, data);
}

void cd_with_param(t_data *data, char *path_value)
{
	if (chdir(path_value) != 0)
	{
		printf("cd: No such file or directory\n");
		return;
	}
	add_env_list(ft_strdup("OLDPWD"), ft_strdup(get_env_value("PWD", data)), data);
	char *newpath = getcwd(NULL, 0);
	if (!newpath)
	{
		perror("cd: getcwd failed\n");
		return;
	}
	add_env_list(ft_strdup("PWD"), ft_strdup(newpath), data);
	free(newpath);
}

int ft_cd(t_data *data)
{
	char *path_value;

	if (!data->words[1])
		cd_with_no_param(data);
	else if (data->words[0] && data->words[1] && !data->words[2])
	{
		path_value = data->words[1];
		if (ft_strncmp("-", path_value, ft_strlen(path_value)) == 0)
			cd_with_dash_param(data);
		else
			cd_with_param(data, path_value);
		return (0);
	}
	else
	{
		if (chdir(data->words[1]) != 0)
			perror("minishell");
	}
	return (0);
}
