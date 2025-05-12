#include "../includes/minishell.h"

bool change_to_home_dir(t_data *data, char *home_dir, int *exit_code)
{
	char *get_pwd;

	if (chdir(home_dir) != 0)
	{
		perror("minishell");
		return (false);
	}
	get_pwd = get_env_value("PWD", data);
	if (get_pwd)
	{
		update_env_list("OLDPWD", get_pwd, data);
		free(get_pwd);
	}
	update_env_list("PWD", home_dir, data);
	return (true);
}

char *expand_path(t_data *data, char *path_value, int *exit_code)
{
	char *expanded;
	char *home;

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