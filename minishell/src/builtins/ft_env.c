#include "../../includes/minishell.h"

int	ft_env(t_cmds *cmd, t_data *data,  int *exit_code)
{
	t_var	*env;

	env = data->env_lst;
	if (cmd->cmd[0] && cmd->cmd[1])
	{
		printf("env: more than one arguments are not supported\n");
		return (-1);
	}
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
