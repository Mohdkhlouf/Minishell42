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

void add_env_var(t_var **list, char *key, char *value)
{
	t_var *update_node;
	char *node;
	
	node = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!node)
		return;
	node[0] = '\0';
    ft_strcat(node, key);     
    ft_strcat(node, "=");     
    ft_strcat(node, value);
	update_node = init_envp_node(node);
	if (update_node)
		env_addtolist(list, update_node);
	free(node);
}


void	init_env(char **envp, t_data *data)
{
	int		i;
	t_var	*list;
	t_var	*node;
	char	cwd[PATH_MAX];

	i = 0;
	list = NULL;
	if (!envp || !envp[0])
	{
		if (getcwd(cwd, sizeof(cwd)))
			add_env_var(&list, "PWD", cwd);
		add_env_var(&list, "SHLVL", "1");
		add_env_var(&list, "_", "/usr/bin/make");	
	}
	else
	{
		while (envp[i])
		{
			node = init_envp_node(envp[i]);
			if (!node)
			{
				free_env_list(list);
				return ;
			}
			env_addtolist(&list, node);
			i++;
		}
	}
	data->env_lst = list;
}

/*mohammad add start*/
void	create_path_arr(char *path, t_data *data)
{
	data->parsed_path = ft_split(path, ':');
	if (!data->parsed_path)
	{
		print_error("creating path arr faild");
		return ;
	}
}
/*mohammad add end*/

void	set_path(t_data *data)
{
	/* Mohammad add start*/
	/*fill in path in main strcut then we have to split using split with :
	so all paths are there then we have to compare with the command so we can
	know if it is existed or not, and we need the right path so we can use it in
	execv function*/
	data->path = get_env_value("PATH", data);
	if (!data->path)
		return ;
	create_path_arr(data->path, data);
	/* Mohammad add end*/
}



// t_var	*init_envp_node(char *env)
// {
// 	t_var	*node;
// 	char	*key;
// 	char	*value;
// 	char	*equal_sign;

// 	equal_sign = ft_strchr(env, '=');
// 	if (!equal_sign)
// 		return (NULL);
// 	node = malloc(sizeof(t_var));
// 	if (!node)
// 		return (NULL);
// 	key = ft_substr(env, 0, equal_sign - env);
// 	value = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
// 	if (!key || !value)
// 	{
// 		return (free(key), free(value), free(node), NULL);
// 	}
// 	node->key = ft_strdup(key);
// 	node->value = ft_strdup(value);
// 	node->next = NULL;
// 	free(key);
// 	free(value);
// 	return (node);
// }

// // Create SHLVL=1
		// node = init_envp_node("SHLVL=1");
		// if (!node)
		// 	return ;
		// env_addtolist(&list, node);
		// // Create PWD=<current_dir>
		// if (getcwd(cwd, sizeof(cwd)))
		// {
		// 	char *pwd_str = malloc(PATH_MAX + 5); // "PWD=" + cwd
		// 	if (!pwd_str)
		// 	{
		// 		free_env_list(list);
		// 		return ;
		// 	}
		// 	sprintf(pwd_str, "PWD=%s", cwd);
		// 	node = init_envp_node(pwd_str);
		// 	free(pwd_str);
		// 	if (!node)
		// 	{
		// 		free_env_list(list);
		// 		return ;
		// 	}
		// 	env_addtolist(&list, node);
		// }
		// data->env_lst = list;
		// return ;