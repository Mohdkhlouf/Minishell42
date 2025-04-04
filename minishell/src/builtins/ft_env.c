#include "../includes/minishell.h"

int ft_env(t_data *data)
{
	t_var *env;
	env = data->env_lst;
	if (data->words[0] && data->words[1])
	{
		printf("env: more than one arguments are not supported\n");
		return (1);
	}
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
// void print_env_to_envp(t_data *data)
// {
// 	t_var *env;

// 	env = data->env_lst;
// 	if (!env)
// 		return;
// 	while (env)
// 	{
// 		if (env->value && env->value[0] == '\0')
// 		{
// 			env = env->next;
// 			continue;
// 		}
// 		if (env->key)
// 			ft_putstr_fd(env->key, 1);
// 		ft_putchar_fd('=', 1);
// 		if (env->value)
// 			ft_putstr_fd(env->value, 1);
// 		ft_putchar_fd('\n', 1);
// 		env = env->next;
// 	}
// }
