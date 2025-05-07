#include "../includes/minishell.h"

bool ft_pwd(t_cmds *cmd, t_data *data, int *exit_code)
{
	(void)cmd;
	char *cwd;

	(void)data;
	*exit_code = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd failed");
		return (false);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (true);
}

// if (cmd->cmd[0] && cmd->cmd[1])
// {
// 	*exit_code = 1;
// 	print_error("minishell: pwd: too many arguments");
// 	exit (*exit_code);
// }
