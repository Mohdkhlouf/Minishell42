#include "../includes/execution.h"

// void execute_command(char **cmd)
// {
// 	printf("execute one Command\n");
// }


// void command_execution(t_parsed_data * cmds)
// {
// 	if (cmds->pipes_counter == 0)
// 	{
// 		execute_command(cmds->cmds[0].cmd);
// 	}
// }


void execution(t_data *data, t_parsed_data *cmds_d)
{
	cmds_process_loop(data, cmds_d);
}