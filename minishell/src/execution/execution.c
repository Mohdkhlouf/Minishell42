#include "../includes/minishell.h"

void execute_redirections(t_data *data, t_parsed_data *cmds_d)
{
	(void) data;
	(void) cmds_d;
	printf("execute redirections\n");
	int i;

	i = 0;
	while (cmds_d->cmds->reds[i])
	{
		printf("redirect %s:\n",cmds_d->cmds->reds[i]);
		i++;
	}
}

void handle_pipes(t_data *data, t_parsed_data *cmds_d)
{
	int prev_cmd = -1;
	int i;
	int j = 0;

	i = 0;
	while(i < cmds_d->cmds_counter)
	{
		execute_pipes(data, cmds_d, i, &prev_cmd);
		//execute_redirections(data, cmds_d);
		//handle_command(&cmds_d->cmds[i], data);
		i++;
	}
	if (prev_cmd != -1)
    	close(prev_cmd);
	while (j < cmds_d->cmds_counter)
	{
        wait(NULL); 
		j++;
	}
}

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

int	execute_builtin(t_data *data, t_cmds *cmds)
{
	if (ft_strncmp(cmds->cmd[0], "echo", ft_strlen("echo")) == 0)
		return (ft_echo(cmds));
	else if (ft_strncmp(cmds->cmd[0], "pwd", ft_strlen("pwd")) == 0)
		return (ft_pwd(cmds));
	else if (ft_strncmp(cmds->cmd[0], "env", ft_strlen("env")) == 0)
		return (ft_env(cmds, data));
	else if (ft_strncmp(cmds->cmd[0], "cd", ft_strlen("cd")) == 0)
		return (ft_cd(cmds, data));
	else if (ft_strncmp(cmds->cmd[0], "export", ft_strlen("export")) == 0)
		return (ft_export(cmds, data));
	else if (ft_strncmp(cmds->cmd[0], "unset", ft_strlen("unset")) == 0)
		return (ft_unset(cmds, data));
	else if (ft_strncmp(cmds->cmd[0], "exit", ft_strlen("exit")) == 0)
		return (ft_exit(cmds));
	return (1);
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
			ret = execute_builtin(data, &cmds_d->cmds[0]);
			if (ret == -1)
				printf("Command not found.\n");
			return ;
		}
		else
			handle_command(&cmds_d->cmds[0], data);
	}
	else
		handle_pipes(data, cmds_d);

	/* Important, when the commmand is empty "" it must be sent to
	be checked ad return error like bash*/

	return ;
}
