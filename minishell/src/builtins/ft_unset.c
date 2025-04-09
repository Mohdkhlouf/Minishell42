#include "../includes/minishell.h"

void update_env_on_unset(t_data *data)
{
	t_var *env;
	char **new_env;
	int i = 0;
	int count = 0;

	env = data->env_lst;
	if(!env)
		return;
	while(env)
	{
		count++;
		env = env->next;
	}
	new_env = malloc(sizeof(char *) * (count + 1));
	if(!new_env)
		return;
	env = data->env_lst;
	while (env)
	{
		if (env->value)
		{
			char *tmp = ft_strjoin(env->key, "=");
			new_env[i] = ft_strjoin(tmp, env->value);
			free(tmp);
			i++;
		}
		env = env->next;
	}
	new_env[i] = NULL;
}

void remove_value_on_unset(char *key, t_data *data)
{
	t_var *env;
	t_var *prev;

	prev = NULL;
	env = data->env_lst;
	if(!env)
		return;
	while(env)
	{
		if(!ft_strcmp(key, env->key))
			break;
		prev = env;
		env = env->next;
	}
	if(env == NULL)
		return;
	if(prev)
		prev->next = env->next;
	else
		data->env_lst = env->next;
	env->next = NULL;
	free(env->key);
	free(env->value);
	free(env);
}

int ft_unset(t_data *data)
{
	if(data->words[0] && !data->words[1])
		return (0);
	int i = 1;
	while(data->words[i])
	{
		remove_value_on_unset(data->words[i], data);
		i++;
	}
	update_env_on_unset(data);
	return (0);
}


//update_env_on_unset(data);
// void print_env(t_var *head)
// {
// 	while (head)
// 	{
// 		printf("%s=%s\n", head->key, head->value);
// 		head = head->next;
// 	}
// }

// void update_env_on_unset(t_data *data)
// {
// 	t_var *env;
// 	// char **new_env;
// 	// int i = 0;
// 	// int count = 0;

// 	env = data->env_lst;
// 	if(!env)
// 		return;
// 	print_env(data->env_lst);
// 	// while(env)
// 	// {
// 	// 	count++;
// 	// 	env = env->next;
// 	// }
// 	// new_env = malloc(sizeof(char *) * (count + 1));
// 	// if(!new_env)
// 	// 	return;
// 	// env = data->env_lst;
// 	// while (env)
// 	// {
// 	// 	if (env->value)
// 	// 	{
// 	// 		char *tmp = ft_strjoin(env->key, "=");
// 	// 		new_env[i] = ft_strjoin(tmp, env->value);
// 	// 		free(tmp);
// 	// 		i++;
// 	// 	}
// 	// 	env = env->next;
// 	// }
// 	// new_env[i] = NULL;
// 	// data->new_envp = new_env;
// }

