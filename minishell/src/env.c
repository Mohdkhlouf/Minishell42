/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:52:20 by akumari           #+#    #+#             */
/*   Updated: 2025/05/20 14:52:22 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_env_var(t_var **list, char *key, char *value)
{
	t_var	*update_node;
	char	*node;

	node = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!node)
		return ;
	node[0] = '\0';
	ft_strcat(node, key);
	ft_strcat(node, "=");
	ft_strcat(node, value);
	update_node = init_envp_node(node);
	if (update_node)
		env_addtolist(list, update_node);
	free(node);
}

void	set_empty_env(t_var **list)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		add_env_var(list, "PWD", cwd);
	add_env_var(list, "SHLVL", "1");
	add_env_var(list, "_", "/usr/bin/make");
}

bool	init_env(char **envp, t_data *data)
{
	int		i;
	t_var	*list;
	t_var	*node;

	i = 0;
	list = NULL;
	if (!envp || !envp[0])
		set_empty_env(&list);
	else
	{
		while (envp[i])
		{
			node = init_envp_node(envp[i]);
			if (!node)
			{
				free_env_list(list);
				return (false);
			}
			env_addtolist(&list, node);
			i++;
		}
	}
	data->env_lst = list;
	return (true);
}

void	create_path_arr(char *path, t_data *data)
{
	data->parsed_path = ft_split(path, ':');
	if (!data->parsed_path)
	{
		print_error("creating path arr faild");
		return ;
	}
}

/*fill in path in main strcut then we have to split using split with :
so all paths are there then we have to compare with the command so we can
know if it is existed or not, and we need the right path so we can use it in
execv function*/
void	set_path(t_data *data)
{
	data->path = get_env_value("PATH", data);
	if (!data->path)
		return ;
	create_path_arr(data->path, data);
}
