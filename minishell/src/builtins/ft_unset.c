#include "../includes/minishell.h"

void update_new_env(t_data *data)
{
	t_var *env;
	char **env_new;
	int i = 0;
	char *temp;

	env = data->env_lst;
	while (env)
	{
		i++;
		env = env->next;
	}
	env_new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	env = data->env_lst;
	while (env)
	{
		if (env->key && env->value) 
		{
			temp = ft_strjoin(env->key, "=");
			if (!temp)
				return;
			env_new[i] = ft_strjoin(temp, env->value);
			free(temp);
			if (!env_new[i])
				return;
			i++;
		}
		env = env->next;
	}
	env_new[i] = NULL;
	data->envp = env_new;
}

void remove_value_on_unset(char *key, t_data *data)
{
	t_var *env;
	t_var *prev;

	prev = NULL;
	env = data->env_lst;
	if (!env)
		return;
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			break;
		prev = env;
		env = env->next;
	}
	if (env == NULL)
		return;
	if (prev)
		prev->next = env->next;
	else
		data->env_lst = env->next;
	env->next = NULL;
	free(env->key);
	free(env->value);
	free(env);
}

int ft_unset(t_cmds *cmd, t_data *data)
{
	if (cmd->cmd[0] && !cmd->cmd[1])
		return (0);
	int i = 1;
	while (cmd->cmd[i])
	{
		remove_value_on_unset(cmd->cmd[i], data);
		i++;
	}
	update_new_env(data);
	return (0);
}

