#include "../includes/minishell.h"

void update_env_list(char *key, char *value, t_data *data)
{
	t_var *env;
	if (!key || !value)
		return;
	env = data->env_lst;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0 && (ft_strlen(env->key) == ft_strlen(key)))
		{
			free(env->value);
			env->value = value;
			return;
		}
		env = env->next;
	}
}

void add_new_env_variable(char *key, char *value, t_data *data)
{
	t_var *new_node;

	if (!key || !value || !data)
		return;

	new_node = malloc(sizeof(t_var));
	if (!new_node)
		return;

	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	env_addtolist(&data->env_lst, new_node);
}
