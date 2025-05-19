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
		if (copy_pwd)
		{
			update_env_list("OLDPWD", copy_pwd, data);
			free(copy_pwd);
		}
		else
			return (false);
	}
	else
	{
		copy_dir = ft_strdup(home_dir);
		if (copy_dir)
		{
			add_new_env_variable("PWD", copy_dir, data);
			free(copy_dir);
		}
		else
			return (false);
	}
	return (true);
}

char	*expand_path(t_data *data, char *path_value, int *exit_code)
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