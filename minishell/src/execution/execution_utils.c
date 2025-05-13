#include "../includes/minishell.h"

/*this function tests if the function is empty then print and return value. it needs more later*/
bool	is_empty_cmd(t_cmds *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "") == 0)
	{
		/*print_error("Command not found.\n");*/
		return (true);
	}
	return (false);
}

/* this function make 2d array for path value from env.
this valuse to if the commands sent is existed or not by comparing it with the values in the path value*/

void	parse_path(t_data *data)
{
	printf("PATH is:%s\n", data->path);
}
