#include "../includes/minishell.h"

int	ft_pwd(t_cmds *cmd, t_data *data)
{
	char	*cwd;

	(void)data;
	if (cmd->cmd[0] && cmd->cmd[1])
	{
		printf("\033[0;31mpwd: too many arguments\033[0m\n");
		return (-1);
	}
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
