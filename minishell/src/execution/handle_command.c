#include "../includes/minishell.h"

/* main function to execute one command, i will make it execute the redirections
then do the command execution*/

void execute_cmd(t_cmds cmd, t_data *data)
{
		(void) data;
	(void)	cmd;
	printf("start execution signle cmd\n");
}

void handle_empty_cmd(t_cmds cmd, t_data *data)
{
	(void) data;
	(void)	cmd;
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
