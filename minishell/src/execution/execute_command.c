#include "../includes/minishell.h"

/* main function to execute one command, i will make it execute the redirections
then do the command execution*/
void handle_empty_cmd(t_cmds cmd, t_data *data)
{
	(void) data;
	(void)	cmd;
	printf("empty cmd handler\n");
}

void	execute_command(t_cmds cmd, t_data *data)
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
			printf("execute command \n"); ;
	}
	else
		handle_empty_cmd(cmd, data);
}
