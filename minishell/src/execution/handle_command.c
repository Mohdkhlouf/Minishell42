#include "../includes/minishell.h"

/* main function to execute one command, i will make it execute the redirections
then do the command execution*/

void exec_cmd(t_cmds cmd, t_data *data)
{
	(void)data;
	(void)cmd;
	// if (execve("pipex->cmds[0].path", cmd.cmd, data->env_lst) == -1)
	// 	exit(1);
}


void	execute_cmd(t_cmds cmd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_error("ERROR IN FORKING\n");
	if (pid == 0)
		exec_cmd(cmd, data);
	
}

void	handle_empty_cmd(t_cmds cmd, t_data *data)
{
	(void)data;
	(void)cmd;
	printf("empty cmd handler\n");
}

void	handle_command(t_cmds cmd, t_data *data)
{
	int	ret;

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
			execute_cmd(cmd, data);
	}
	else
		handle_empty_cmd(cmd, data);
}
