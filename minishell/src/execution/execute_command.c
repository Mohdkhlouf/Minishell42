#include "../includes/minishell.h"

/* main function to execute one command, i will make it execute the redirections
then do the command execution*/

void	execute_command(t_cmds cmd)
{
	if(!is_empty_cmd(cmd))
		printf("TEsing cmds %s\n", cmd.cmd[0]);
	else
		return;
}