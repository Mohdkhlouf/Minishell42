#include "../../includes/minishell.h"

bool	ft_env(t_cmds *cmd, t_data *data, int *exit_code)
{
	t_var	*env;

	env = data->env_lst;
	if (cmd->cmd[0] && cmd->cmd[1])
	{
		if (access(cmd->cmd[1], F_OK) == -1)
		{
			minishell_error("env", "No such file or directory", cmd->cmd[1]);
			*exit_code = 127;
		}
		else if (access(cmd->cmd[1], X_OK) == 0)
		{
			minishell_error("env", "Permission denied", cmd->cmd[1]);
			*exit_code = 126;
		}
		return (false);
	}
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	*exit_code = 0;
	return (true);
}
