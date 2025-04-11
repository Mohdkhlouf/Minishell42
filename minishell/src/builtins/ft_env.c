#include "../../includes/minishell.h"

int ft_env(t_cmds *cmd, t_data *data)
{
	t_var *env;

	env = data->env_lst;
	if (cmd->cmd[0] && cmd->cmd[1])
	{
		printf("\033[0;31menv: more than one arguments are not supported\033[0m\n");
		return (-1);
	}
	while (env)
	{
		if (env->value)
			printf("\033[0;32m%s=%s\033[0m\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

// int ft_env(t_data *data)
// {
// 	t_var *env;

// 	env = data->env_lst;
// 	if (data->words[0] && data->words[1])
// 	{
// 		printf("\033[0;31menv: more than one arguments are not supported\033[0m\n");
// 		return (1);
// 	}
// 	while (env)
// 	{
// 		if (env->value)
// 			printf("\033[0;32m%s=%s\033[0m\n", env->key, env->value);
// 		env = env->next;
// 	}
// 	return (0);
// }