#include "../includes/minishell.h"

int	ft_pwd(t_cmds *cmd, t_data *data, int *exit_code)
{
	char	*cwd;

	(void)data;
	if (cmd->cmd[0] && cmd->cmd[1])
	{
		*exit_code = 1;
		print_error("minishell: pwd: too many arguments");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd failed");
		return (-1);
	}
	printf("%s\n", cwd);
	free(cwd);
	*exit_code = 0;
	return (0);
}
