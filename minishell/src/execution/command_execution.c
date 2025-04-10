#include "../includes/minishell.h"

char *join_cmd_with_slash(char *cmd)
{
	char *result;

	result = NULL;
	result = ft_strjoin("/", cmd);
	if(!result)
		print_error("Join is not done\n");
	return (result);
}

char	*find_path(t_data *data, char *cmd)
{
	int		i;
	char	*file_name;
	int		not_found;

	not_found = 0;
	i = 0;
	file_name = NULL;
	cmd = join_cmd_with_slash(cmd);
	while (data->parsed_path[i])
	{
		if (i != 0)
			free(file_name);
		file_name = ft_strjoin(data->parsed_path[i], cmd);
		if (!file_name)
			print_error("Join is not done\n");
		if ((access(file_name, F_OK) == 0))
			return (file_name);
		else
			not_found = 1;
		i++;
	}
	if (not_found == 1)
		print_error("FILE NOT FOUNT\n");
	return (NULL);
}

void exec_cmd(t_cmds cmd, t_data *data)
{
	(void)data;
	(void)cmd;
	char *path;

	path = NULL;
	path = find_path(data, cmd.cmd[0]);
	if (execve(path, cmd.cmd, NULL) == -1)
		exit(1);
}

/* this function will start the fork to execute the cmd
i did the fork here.
then send the execution to child process*/
int	execute_cmd(t_cmds cmd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_error("ERROR IN FORKING\n");
	if (pid == 0)
		exec_cmd(cmd, data);
	return (pid);
}
/*to handlle any empty cmd*/
void	handle_empty_cmd(t_cmds cmd, t_data *data)
{
	(void)data;
	(void)cmd;
	printf("empty cmd handler\n");
}
