#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	const char	*builtins[] = {"cd", "exit", "echo", "pwd", "export", "unset",
			"env", NULL};
	int			i;

	i = 0;

	while (builtins[i] != NULL)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute_builtin(t_data *data, t_parsed_data *cmds_data)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	count = 0;
	j = 0;
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


void execute_pipes(t_data *data, t_parsed_data *cmds_d)
{
	(void) data;
	(void) cmds_d;
	int i;

	i = 0;
	while(i < cmds_d->cmds_counter)
	{
		handle_command(cmds_d->cmds[i], data);
		i++;
	}
	
}

void	execution(t_data *data, t_parsed_data *cmds_d)
{
	int ret;
	int i = 0;

	if (!data || !cmds_d)
		return ;

	// parse_path(data);

	if (cmds_d->cmds_counter == 0)
		return ;
	else if (cmds_d->cmds_counter == 1)
	{
		if (is_builtin(cmds_d->cmds[i].cmd[0]) == 1)
		{
			ret = execute_builtin(data, cmds_d);
			if (ret == -1)
				printf("Command not found.\n");
			return ;
		}
		else
			handle_command(cmds_d->cmds[0], data);
	}
	else
		execute_pipes(data, cmds_d);

	/* Important, when the commmand is empty "" it must be sent to
	be checked ad return error like bash*/

	return ;
}