#include "../includes/minishell.h"

int	ft_pwd(t_cmds *cmd, t_data *data, int *exit_code)
{
	char	*cwd;

	(void)data;
	*exit_code = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd failed");
		return (-1);
	}
	printf("%s\n", cwd);
	free(cwd);

	return (0);
}

	// if (cmd->cmd[0] && cmd->cmd[1])
	// {
	// 	*exit_code = 1;
	// 	print_error("pwd: too many arguments");
	// 	exit(*exit_code);
	// }