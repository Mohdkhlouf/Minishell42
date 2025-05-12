#include "../includes/minishell.h"

bool	ft_pwd(t_cmds *cmd, t_data *data, int *exit_code)
{
	char	*cwd;

	(void)cmd;
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
