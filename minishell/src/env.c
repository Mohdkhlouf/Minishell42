#include "../includes/minishell.h"

char *get_env_value(char *key, t_data *data)
{
	t_var *env;

	env = data->env_lst;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0 && (ft_strlen(env->key) == ft_strlen(key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void env_addtolist(t_var **lst, t_var *node)
{
	t_var *current;

	if (!lst || !node)
		return;
	if (!*lst)
	{
		*lst = node;
		return;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}

t_var *init_envp_node(char *env)
{
	t_var *node;
	char *key;
	char *value;
	char *equal_sign;

	equal_sign = ft_strchr(env, '=');
	if (!equal_sign)
		return (NULL);
	node = malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	key = ft_substr(env, 0, equal_sign - env);
	value = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
	if (!key || !value)
	{
		return (free(key), free(value), free(node), NULL);
	}
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void init_env(char **envp, t_data *data)
{
	int i;
	t_var *list;
	t_var *node;

	i = 0;
	list = NULL;
	if (!envp)
		return;
	while (envp[i])
	{
		node = init_envp_node(envp[i]);
		if (!node)
		{
			free_env_list(list);
			return;
		}
		env_addtolist(&list, node);
		i++;
	}
	data->env_lst = list;
}
