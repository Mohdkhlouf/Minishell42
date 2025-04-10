#include "../includes/minishell.h"

/* main function to execute one command, i will make it execute the redirections
then do the command execution*/


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
