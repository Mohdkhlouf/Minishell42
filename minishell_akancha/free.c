#include "main.h"

void free_env_list(t_var *node)
{
	t_var *tmp;
	while (node)
	{
		tmp = node;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		node = node->next;
	}
}

int free_matrix(char **env)
{
	int i;

	if (!env)
		return (1);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (0);
}
