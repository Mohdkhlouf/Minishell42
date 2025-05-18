#include "../includes/minishell.h"

void	env_addtolist(t_var **lst, t_var *node)
{
	t_var	*current;

	if (!lst || !node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}

t_var	*init_envp_node(char *env)
{
	t_var	*node;
	char	*equal_sign;

	equal_sign = ft_strchr(env, '=');
	if (!equal_sign)
		return (NULL);
	node = malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->key = ft_substr(env, 0, equal_sign - env);
	node->value = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}
