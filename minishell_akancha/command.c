#include "main.h"

int is_builtin(char *cmd)
{
	const char *builtins[] = {
		"cd",
		"exit",
		"echo",
		"pwd",
		"export",
		"unset",
		"env",
		NULL};
	int i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int execute_builtin(t_data *data)
{
	data->words = ft_split(data->cmd, ' ');
	if (!data->words)
	{
		printf("Error: Memory allocation failed\n");
		return (1);
	}
	if (ft_strncmp(data->words[0], "echo", ft_strlen("echo")) == 0)
		return (ft_echo(data));
	else if (ft_strncmp(data->words[0], "pwd", ft_strlen("pwd")) == 0)
		return (ft_pwd(data));
	else if (ft_strncmp(data->words[0], "env", ft_strlen("env")) == 0)
		return (ft_env(data));
	else if (ft_strncmp(data->words[0], "cd", ft_strlen("cd")) == 0)
		return (ft_cd(data));
	else if (ft_strncmp(data->words[0], "export", ft_strlen("export")) == 0)
		return (ft_export(data));
	return (1);
}

int cmds_process_loop(t_data *data)
{
	int ret;
	if (!data || !data->cmd)
		return (1);
	if (is_builtin(data->cmd) == 1)
	{
		ret = execute_builtin(data);
		if (ret == -1)
			printf("Command not found.\n");
		return (0);
	}
	return (1);
}
