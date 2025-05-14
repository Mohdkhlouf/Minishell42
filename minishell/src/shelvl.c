#include "../includes/minishell.h"

t_var *get_env_lst(t_var *env_lst, const char *key)
{
	while (env_lst)
	{
		if (strcmp(env_lst->key, key) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void shelvl(t_data *data)
{
	t_var *env_var;
	int shell_level = 1;
	char *shlvl_str;

	env_var = get_env_lst(data->env_lst, "SHLVL");
	if (env_var)
		shell_level = ft_atoi(env_var->value) + 1;
	shlvl_str = ft_itoa(shell_level);
	update_env_list("SHLVL", shlvl_str, data);
	free(shlvl_str);
}

void exit_shlvl(t_data *data)
{
	t_var *env_var;
	char *shlvl_str;
	env_var = get_env_lst(data->env_lst, "SHLVL");
	if (env_var)
	{
		int shell_level = ft_atoi(env_var->value);
		if (shell_level > 2)
		{
			shell_level--;
			shlvl_str = ft_itoa(shell_level);
			update_env_list("SHLVL", shlvl_str, data);
			free(shlvl_str);
		}
	}
}
