#include "../includes/minishell.h"

/* main function to execute one command, i will make it execute the redirections
then do the command execution*/

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

/*this function recieved a cmd struct, first i check if the command is empty
then if not, check if it is a built in, then will execute as built in.
if not, i use another function to start executing the external cmd*/
void	handle_command(t_cmds cmd, t_data *data)
{
	int	ret;
	int pid[1];
	int status;


	ret = 0;
	(void)data;
	if (!is_empty_cmd(cmd))
	{
		if (is_builtin(cmd.cmd[0]) == 1)
		{
			/*function to execute builtin function the sent will be a command*/
			printf("execute builtin \n");
		}
		else
			pid[0] = execute_cmd(cmd, data);
	}
	else
		handle_empty_cmd(cmd, data);
	waitpid(pid[0], &status, 0);
}
