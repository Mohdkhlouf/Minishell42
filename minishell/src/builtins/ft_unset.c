#include "../includes/minishell.h"

static bool	fill_env_array(t_var *env, char **env_new)
{
	int		i;
	char	*temp;

	i = 0;
	while (env)
	{
		if (env->key && env->value)
		{
			temp = ft_strjoin(env->key, "=");
			if (!temp)
				return (false);
			env_new[i] = ft_strjoin(temp, env->value);
			free(temp);
			if (!env_new[i])
				return (false);
			i++;
		}
		env = env->next;
	}
	env_new[i] = NULL;
	return (true);
}

bool	update_new_env(t_data *data)
{
	t_var	*env;
	char	**env_new;
	int		i;

	if (data->envp)
		free_matrix(data->envp);
	i = 0;
	env = data->env_lst;
	while (env)
	{
		i++;
		env = env->next;
	}
	env_new = malloc(sizeof(char *) * (i + 1));
	if (!env_new)
		return (false);
	if (!fill_env_array(data->env_lst, env_new))
		return (false);
	data->envp = env_new;
	return (true);
}

void	remove_value_on_unset(char *key, t_data *data)
{
	t_var	*env;
	t_var	*prev;

	prev = NULL;
	env = data->env_lst;
	if (!env)
		return ;
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			break ;
		prev = env;
		env = env->next;
	}
	if (env == NULL)
		return ;
	if (prev)
		prev->next = env->next;
	else
		data->env_lst = env->next;
	env->next = NULL;
	free(env->key);
	free(env->value);
	free(env);
}

bool	ft_unset(t_cmds *cmd, t_data *data, int *exit_code)
{
	int	i;

	if (cmd->cmd[0] && !cmd->cmd[1])
		return (true);
	i = 1;
	while (cmd->cmd[i])
	{
		remove_value_on_unset(cmd->cmd[i], data);
		i++;
	}
	update_new_env(data);
	*exit_code = 0;
	return (true);
}
