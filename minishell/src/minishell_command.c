#include "../includes/minishell.h"
#include "../includes/parsing.h"

int is_builtin(char *cmd)
{
	const char *builtins[] = {"cd", "exit", "echo", "pwd", "export", "unset",
							  "env", NULL};
	int i;

	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int execute_builtin(t_data *data, t_parsed_data *cmds_data)
{
	int i = 0;
	int count = 0;
	int j = 0;

	while (cmds_data->cmds[0].cmd[i])
	{
		count++;
		i++;
	}
	data->words = malloc(sizeof(char *) * (count + 1));
	if (!data->words)
	{
		perror("malloc allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	while (j < count)
	{
		data->words[j] = ft_strdup(cmds_data->cmds[0].cmd[j]);
		if (!data->words[j])
		{
			perror("ft_strdup failed\n");
			exit(EXIT_FAILURE);
		}
		j++;
	}
	data->words[j] = NULL;
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
	else if (ft_strncmp(data->words[0], "unset", ft_strlen("unset")) == 0)
		return (ft_unset(data));
	return (1);
}

void cmds_process_loop(t_data *data, t_parsed_data *cmds_data)
{
	int ret;
	int i = 0;
	int j = 0;

	if (!data || !cmds_data)
		return;
	/* Important, when the commmand is empty "" it must be sent to
	be checked ad return error like bash*/
	if (ft_strcmp(cmds_data->cmds[0].cmd[0], "") == 0)
	{
		printf("Command not found.\n");
		return;
	}
	if (is_builtin(cmds_data->cmds[i].cmd[j]) == 1)
	{
		ret = execute_builtin(data, cmds_data);
		if (ret == -1)
			printf("Command not found.\n");
		return;
	}
	return;
}
